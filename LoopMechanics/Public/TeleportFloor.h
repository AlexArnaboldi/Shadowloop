// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportFloor.generated.h"

class USLSaveGame;
class UGameOverComponent;
class ACustomPlayer;
class UCheckPuzzleComponent;
class URelocateMovableObject;

UCLASS()
class SHADOWLOOP_API ATeleportFloor : public AActor
{
	GENERATED_BODY()
protected:
	// ------------------------------ Componets ------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<USceneComponent> Root = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Components")
	TObjectPtr<UStaticMeshComponent> FloorMesh = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category= "Components | Check puzzle")
	TObjectPtr<UCheckPuzzleComponent> CheckPuzzleComponent = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category= "Components | Check puzzle")
	TObjectPtr<URelocateMovableObject> RelocateMovableObject = nullptr;
protected:
	// ------------------------------ Variable ------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Teleport | Destination")
	TWeakObjectPtr<ATeleportFloor> LevelUpDestination = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Teleport | Destination")
	TWeakObjectPtr<ATeleportFloor> RestartDestination = nullptr;
	
	UPROPERTY(BlueprintReadOnly, Category= "Teleport | Destination")
	bool bIsPuzzleSolved = false;

	UPROPERTY(BlueprintReadOnly, Category= "Gameover")
	TObjectPtr<UGameOverComponent> GameOverComponent = nullptr;
private:
	UPROPERTY()
	TWeakObjectPtr<ACustomPlayer> Player = nullptr;

public:
	bool GetIsPuzzleSolved() { return bIsPuzzleSolved; };
	void SetIsPuzzleSolved(bool InIsPuzzleSolved) { bIsPuzzleSolved = InIsPuzzleSolved; };
public:
	ATeleportFloor();

protected:
	virtual void BeginPlay() override;

private:
	// get the Vector from the center to the player
	FVector SubtractionVectorPlayerFloor(FVector InPointOfPlayer);
	
	// get the angle
	float AngleRotationYaw(ATeleportFloor* InDestinationFloor);

	// Rotate the Vector by the angle
	FVector RotateVector(FVector TeleportVector, float InAngleRotation);
	
	UFUNCTION(BlueprintCallable)
	void SetTeleportLocation(FVector InPointOfPlayer, float InDistanceFromFloor, ATeleportFloor* InDestinationFloor, FVector& SavePlayerLoc);

	UFUNCTION(BlueprintCallable)
	void SetVelocityAndCameraRotation(ATeleportFloor* InDestinationFloor);

	UFUNCTION(BlueprintCallable)
	void SaveGameSlot(const FVector InStartPlayerLoc, const int InCurrentLevel);
};
