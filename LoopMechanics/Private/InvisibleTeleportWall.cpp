
#include "InvisibleTeleportWall.h"

#include "CustomPlayer.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AInvisibleTeleportWall::AInvisibleTeleportWall()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(Root);
	
	PrimaryActorTick.bCanEverTick = false;
}

void AInvisibleTeleportWall::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ACustomPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomPlayer::StaticClass()));
	ensureMsgf(Player.IsValid(), TEXT("Player pointer is not valid"));

	if (!IsValid(BoxCollision)){return;}

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AInvisibleTeleportWall::BegingOverlap);
}

void AInvisibleTeleportWall::BegingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!Player.IsValid()){return;}
	
	if (OtherActor == Player)
	{
		Player->TeleportActive();
	}
}

