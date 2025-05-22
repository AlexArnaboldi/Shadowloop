
#include "TeleportFloor.h"

#include "CustomPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CheckPuzzleComponent.h"
#include "RelocateMovableObject.h"
#include "SaveGame/SLSaveGame.h"


ATeleportFloor::ATeleportFloor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(Root);

	CheckPuzzleComponent = CreateDefaultSubobject<UCheckPuzzleComponent>(TEXT("CheckPuzzleComponent"));

	RelocateMovableObject = CreateDefaultSubobject<URelocateMovableObject>(TEXT("RelocateMovableObjec"));
	
	PrimaryActorTick.bCanEverTick = false;
}

void ATeleportFloor::BeginPlay()
{
	Super::BeginPlay();

	bIsPuzzleSolved = false;

	Player = Cast<ACustomPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomPlayer::StaticClass()));
	ensureMsgf(Player.IsValid(), TEXT("Player is invalid"));
	if (!Player.IsValid()) {return;}
	
	GameOverComponent = Player->GetGameOverComponent();
	ensureMsgf(GameOverComponent, TEXT("GameOverComponent is not valid"));
}

FVector ATeleportFloor::SubtractionVectorPlayerFloor(FVector InPointOfPlayer)
{
	FVector SubtractVector = (InPointOfPlayer * -1) + FloorMesh->GetComponentLocation();
	return SubtractVector;
}

float ATeleportFloor::AngleRotationYaw(ATeleportFloor* InDestinationFloor)
{
	float AngleRotatio = InDestinationFloor->GetActorRotation().Yaw - GetActorRotation().Yaw;
	return AngleRotatio;
}

FVector ATeleportFloor::RotateVector(FVector TeleportVector, float InAngleRotation)
{
	FVector RotationAxis = FVector(0.f, 0.f, 1.0f);
	FVector RotatedVector = TeleportVector.RotateAngleAxis(InAngleRotation, RotationAxis);
	return RotatedVector;
}

void ATeleportFloor::SetTeleportLocation(FVector InPointOfPlayer, float InDistanceFromFloor, ATeleportFloor* InDestinationFloor, FVector& SavePlayerLoc)
{
	if (!Player.IsValid()) { return; }
	if (!IsValid(InDestinationFloor))
	{
		UE_LOG(LogTemp, Error, TEXT("DestinationFloor is not correct"));
		return;
	}
	
	//Vector Player Teleport X,Y
	FVector TeleportDestination = InDestinationFloor->GetActorLocation()
			- RotateVector(SubtractionVectorPlayerFloor(InPointOfPlayer), AngleRotationYaw(InDestinationFloor));
	//Vector Player Teleport Z
	TeleportDestination.Z += InDistanceFromFloor;
	
	Player->SetActorLocation(TeleportDestination);

	SavePlayerLoc = InDestinationFloor->GetActorLocation();
	SavePlayerLoc.Z += InDistanceFromFloor;
	
	// SaveGameSlot(SavePlayerLoc);
	//
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *SavePlayerLoc.ToString())
}

void ATeleportFloor::SetVelocityAndCameraRotation(ATeleportFloor* InDestinationFloor)
{
	if (!Player.IsValid()) { return; }
	if (!IsValid(InDestinationFloor))
	{
		UE_LOG(LogTemp, Error, TEXT("DestinationFloor is not correct"));
		return;
	}

	// Change velocity
	FVector NewVelocity = RotateVector(Player->GetCharacterMovement()->Velocity, AngleRotationYaw(InDestinationFloor));
	Player->GetCharacterMovement()->Velocity = NewVelocity;

	// change camera	
	FRotator NewCameraRotation =
		FRotator(Player->GetController()->GetControlRotation().Pitch,
				Player->GetController()->GetControlRotation().Yaw + AngleRotationYaw(InDestinationFloor),
							Player->GetController()->GetControlRotation().Roll);
	Player->GetController()->SetControlRotation(NewCameraRotation);
}

void ATeleportFloor::SaveGameSlot(FVector InStartPlayerLoc, int InCurrentLevel)
{
	if (USLSaveGame* SaveGameInstance = Cast<USLSaveGame>(UGameplayStatics::CreateSaveGameObject(USLSaveGame::StaticClass())))
	{
		// Set data on the savegame object.
		SaveGameInstance->StartPlayerLoc = InStartPlayerLoc;

		SaveGameInstance->CurrentLevel = InCurrentLevel;
			
		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, "SaveOneSlot", 0);

		UE_LOG(LogTemp, Warning, TEXT("Saved save slot"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to save save slot"));
	}
}
