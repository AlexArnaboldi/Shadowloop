// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvisibleTeleportWall.generated.h"

class ACustomPlayer;
class UBoxComponent;

UCLASS()
class SHADOWLOOP_API AInvisibleTeleportWall : public AActor
{
	GENERATED_BODY()
protected:
	// ------------- Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	TObjectPtr<UBoxComponent> BoxCollision = nullptr;

	// ------------- Player pointer
	TWeakObjectPtr<ACustomPlayer> Player = nullptr;
public:
	AInvisibleTeleportWall();

protected:
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void BegingOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
