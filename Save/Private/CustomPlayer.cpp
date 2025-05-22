// Fill out your copyright notice in the Description page of Project Settings.

#include "ShadowLoop/Public/CustomPlayer.h"

#include "GameOverComponent.h"
#include "ShadowLoop/Public/ObjectInteractionComponent.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SLSaveGame.h"


// Sets default values
ACustomPlayer::ACustomPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GameOverComponent = CreateDefaultSubobject<UGameOverComponent>(TEXT("GameOverComponent"));
}

void ACustomPlayer::CastRayFromCamera(UPrimitiveComponent*& OutHitComponent, AActor*& OutHitActor)
{
	checkf(IsValid(FirstPersonCameraComponent), TEXT("No Camera found"));
	if (!IsValid(FirstPersonCameraComponent)) { return; };
	FHitResult HitResult;
	FVector StartPoint = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndPoint = FirstPersonCameraComponent->GetForwardVector() * InteractionDistance + StartPoint;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this->GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, Params))
	{
		OutHitComponent = HitResult.Component.Get();
		OutHitActor = HitResult.GetActor();
	}
	else
	{
		OutHitComponent = nullptr;
		OutHitActor = nullptr;
	}

	if (EnableDebugLine)
	{
		DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Red, false, 1.0f);
	}
}


void ACustomPlayer::CastSphereTraceFromCamera(UPrimitiveComponent*& OutHitComponent, AActor*& OutHitActor)
{
	checkf(IsValid(FirstPersonCameraComponent), TEXT("No Camera found"));
	if (!IsValid(FirstPersonCameraComponent)) { return; };
	FHitResult HitResult;
	FVector StartPoint = FirstPersonCameraComponent->GetComponentLocation();
	FVector EndPoint = FirstPersonCameraComponent->GetForwardVector() * InteractionDistance + StartPoint;
	FCollisionQueryParams Params;
	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(Owner);
	Params.AddIgnoredActor(this->GetOwner());

	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(), StartPoint, EndPoint, RadiusSphereTrace,
	                                            UEngineTypes::ConvertToTraceType(ECC_Visibility)
	                                            , false, IgnoreActors,
	                                            EDrawDebugTrace::ForDuration, HitResult, true))
	{
		OutHitComponent = HitResult.Component.Get();
		OutHitActor = HitResult.GetActor();
	}
	else
	{
		OutHitComponent = nullptr;
		OutHitActor = nullptr;
	}
}

void ACustomPlayer::LoadGame()
{
	if (UGameplayStatics::DoesSaveGameExist("SaveOneSlot", 0))
	{
		// set delegate
		FAsyncLoadGameFromSlotDelegate LoadedDelegate;
		LoadedDelegate.BindUObject(this, &ACustomPlayer::LoadGameDelegateFunction);

		UGameplayStatics::AsyncLoadGameFromSlot("SaveOneSlot", 0, LoadedDelegate);
		UE_LOG(LogTemp, Display, TEXT("Loading Game Slot %hs"), "SaveOneSlot");
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("%hs doesn't exist"), "SaveOneSlot");
	}
}

void ACustomPlayer::LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	USLSaveGame* MySaveGame = Cast<USLSaveGame>(LoadedGameData);

	SetActorLocation(MySaveGame->StartPlayerLoc);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *MySaveGame->StartPlayerLoc.ToString())
	GetGameOverComponent()->SetCurrentLevel(MySaveGame->CurrentLevel);
}
