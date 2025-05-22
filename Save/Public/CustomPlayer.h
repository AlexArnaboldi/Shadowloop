// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowLoop/ShadowLoopCharacter.h"
#include "CustomPlayer.generated.h"

class USLSaveGame;
class UGameOverComponent;
class ASLHUDGame;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivateGrabPrompt, bool, InIsPlayerLookingAtObject);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCountNearMovableObjects, bool, InIsMovableObjectNear);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectGrabbed, bool, InIsObjectGrabbed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectAttachedToStand, bool, InIsObjectAttachedToStand);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRotationModeActivated, bool, InRotationModeActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorNear, bool, InIsDoorNear);

UCLASS(config=Game)
class SHADOWLOOP_API ACustomPlayer : public AShadowLoopCharacter
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "CustomPlayer | Interaction")
	void CastRayFromCamera (UPrimitiveComponent*& OutHitComponent, AActor*& OutHitActor);

	UFUNCTION(BlueprintCallable, Category = "CustomPlayer | Interaction")
	void CastSphereTraceFromCamera (UPrimitiveComponent*& OutHitComponent, AActor*& OutHitActor);

public:
	ACustomPlayer();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UGameOverComponent> GameOverComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CustomPlayer | Interaction")
	int32 InteractionDistance = 500;

	UPROPERTY(EditAnywhere, Category="CustomPlayer | Interaction")
	bool EnableDebugLine = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="CustomPlayer | Interaction")
	float RadiusSphereTrace = 10.f;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void TeleportActive();

	virtual UObjectInteractionComponent* GetObjectInteractionComponent() const override { return ObjectInteractionComponent; }

	// ------------------- Game Over ------------------- //
	UGameOverComponent* GetGameOverComponent() { return GameOverComponent; };

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GameOver")
	void GameOver();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
	void Counter25();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
	void Counter50();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
	void Counter75();

	UFUNCTION(BlueprintImplementableEvent, Category = "GameOver")
	void RotateCharacterToEnemy();
	
	// ------------------- Prompt ------------------- //
	FOnActivateGrabPrompt OnActivateGrabPrompt;
	FOnCountNearMovableObjects OnCountNearMovableObjects;
	FOnObjectGrabbed OnObjectGrabbed;
	FOnObjectAttachedToStand OnObjectAttachedToStand;
	FOnRotationModeActivated OnRotationModeActivated;
	FOnDoorNear OnDoorNear;

// ------------------- Pause Page In------------------- //
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsAddPageMenu = false;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddPausePage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemovePausePage();
// ------------------- Pause Page Out------------------- //
	
// ------------------- GameOver Page In------------------- //
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsAddPageGameOver = false;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddGameOverPage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveGameOverPage();
// ------------------- GameOver Page Out------------------- //

// ------------------- Credits Page In------------------- //
protected:
	UPROPERTY(BlueprintReadWrite)
	bool bIsAddPageCredits = false;
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AddCreditsPage();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemoveCreditsPage();
// ------------------- Credits Page Out------------------- //

	UFUNCTION(BlueprintCallable)
	void LoadGame();
	
	UFUNCTION()
	void LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);
};