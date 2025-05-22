
#include "ShadowLoop/Public/TeleportDoor.h"

#include "CustomPlayer.h"
#include "ObjectInteractionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ATeleportDoor::ATeleportDoor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SetScale = CreateDefaultSubobject<USceneComponent>(TEXT("Scale"));
	SetScale->SetupAttachment(Root);

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrameMesh->SetupAttachment(SetScale);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(SetScale);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	Box->SetupAttachment(SetScale);

	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
	PrimaryActorTick.bCanEverTick = true;

	// ------------------- Prompt ------------------- //
	PromptBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PromptBox"));
	PromptBox->SetupAttachment(SetScale);
	PromptBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATeleportDoor::BeginPlay()
{
	Super::BeginPlay();

	ensureMsgf(IsValid(DoorCurve), TEXT("DoorCure is invalid"));
	if (!IsValid(DoorCurve)) { return; }
	
	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, FName("OpenCloseDoorTimeline"));
	DoorTimeline->AddInterpFloat(DoorCurve, ProgressFunction);

	FOnTimelineEvent EndEvent;
	EndEvent.BindUFunction(this, FName("FinishTimeline"));
	DoorTimeline->SetTimelineFinishedFunc(EndEvent);
	
	Player = Cast<ACustomPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomPlayer::StaticClass()));
	ensureMsgf(Player.IsValid(), TEXT("Player is invalid"));

	// ------------------- Prompt ------------------- //
	if (!PromptBox) { return; }
	PromptBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleportDoor::OnBeginOverlap);
	PromptBox->OnComponentEndOverlap.AddDynamic(this, &ATeleportDoor::OnEndOverlap);
}

void ATeleportDoor::WhichSideOpen()
{
	ensureMsgf(Player.IsValid(), TEXT("Player is invalid"));
	if (!Player.IsValid()) { return; }
	
	FVector PlayerDirection = Player->GetActorForwardVector();
	FVector DoorDirection = this->GetActorForwardVector();

	if (FVector::DotProduct(PlayerDirection, DoorDirection) >= 0.0f)
	{
		OpenRotation = FRotator(0.0f, AngleDoorOpenCLose, 0.0f);
		bOpenSide = true;
	}
	else
	{
		bOpenSide = false;
	}
}

void ATeleportDoor::OpenCloseDoorTimeline(float Alpha)
{
	FRotator CurrentRotation = FMath::Lerp(StartRotation, OpenRotation, Alpha);
	DoorMesh->SetRelativeRotation(CurrentRotation);
}

void ATeleportDoor::FinishTimeline()
{
	if (bIsOpen == true)
	{
		// --------------------------------- DOOR IS OPEN ---------------------------------
		bIsMoving = false;
		LevelSequenceEvent();
	}
	else
	{
		// --------------------------------- DOOR IS CLOSE ---------------------------------
		bIsMoving = false;
		if (!bIsTeleport){return;}
		Player->TeleportActive();
	}
}

void ATeleportDoor::CallPlayerTeleport()
{
	ensureMsgf(Player.IsValid(), TEXT("Player is invalid"));
	if (!Player.IsValid()) { return; }
	
	Player->TeleportActive();
}

/*
void ATeleportDoor::TimeLineDoor()
{
	if (bCanBeOpen)
	{
		// --------------------------------- DOOR IS OPENING ---------------------------------
		if (bIsOpen == false && bIsMoving == false)
		{
			OpenDoor();
		}
		// --------------------------------- DOOR IS CLOSING ---------------------------------
		else if (bIsOpen == true && bIsMoving == false)
		{
			CloseDoor();
		}
	}
}
*/

void ATeleportDoor::OpenDoor()
{
	if (bIsMoving){return;}
	
	WhichSideOpen();
	if (!bOpenSide){return;}
	
	DoorTimeline->Play();
	bIsMoving = true;
	bIsOpen = true;
}

void ATeleportDoor::CloseDoor()
{
	if (bIsMoving){return;}
	DoorTimeline->Reverse();
	
	bIsMoving = true;
	bIsOpen = false;
}


// ------------------- Prompt ------------------- //

void ATeleportDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomPlayer* OverlappingPlayer = Cast<ACustomPlayer>(OtherActor);
	if (!IsValid(OverlappingPlayer)) { return; }
	
	bIsPlayerInPromptBox = true;
}

void ATeleportDoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACustomPlayer* OverlappingPlayer = Cast<ACustomPlayer>(OtherActor);
	if (!IsValid(OverlappingPlayer)) { return; }
	
	bIsPlayerInPromptBox = false;
	
	if (!OverlappingPlayer->GetObjectInteractionComponent()->GetIsGrabbingObject())
	{
		OverlappingPlayer->OnDoorNear.Broadcast(false);
	}
	
	bIsPlayerLookingAtDoor = false;
}

void ATeleportDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!Player.IsValid()) { return; }
	if (Player->GetObjectInteractionComponent()->GetIsGrabbingObject()) { return; }
	if (bIsPlayerInPromptBox)
	{
		ActivatePrompt();
	}
}

void ATeleportDoor::ActivatePrompt()
{
	ensureMsgf(Player.IsValid(), TEXT("Player is invalid"));
	if (!Player.IsValid()) {return ;}

	UCameraComponent* Camera = Player->GetFirstPersonCameraComponent();
	FVector PlayerDirection = Camera->GetForwardVector();
	
	FVector DoorPosition = GetActorLocation();
	DoorPosition.Z += PromptOffset;
	FVector PlayerPosition = Camera->GetComponentLocation();

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(PlayerPosition, DoorPosition);
	FVector LookAtVector = UKismetMathLibrary::GetForwardVector(LookAtRotation);

	float DotProduct = FVector::DotProduct(PlayerDirection, LookAtVector);
	double angle = UKismetMathLibrary::MapRangeClamped(DotProduct, -1, 1, 180, 0);
	if (angle <= PromptTolerance && !bIsPlayerLookingAtDoor)
	{
		Player->OnDoorNear.Broadcast(true);
		bIsPlayerLookingAtDoor = true;
	}
	else if (angle > PromptTolerance && bIsPlayerLookingAtDoor)
	{
		Player->OnDoorNear.Broadcast(false);
		bIsPlayerLookingAtDoor = false;
	}
}


