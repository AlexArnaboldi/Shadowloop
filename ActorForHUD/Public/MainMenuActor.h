// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuActor.generated.h"

class USLButtonContinue_M;
class USLButtonPlay_M;
class USLHUDWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewGameButton, float, ProgressBarNewGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnContinueButton, float, ProgressBarContinue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuitButton);

UENUM(BlueprintType)
enum class EWhichBook : uint8
{
	NewGame UMETA(DisplayName = "New Game"),
	Continue UMETA(DisplayName = "Continue"),
	Quit UMETA(DisplayName = "Quit")
};

UCLASS()
class SHADOWLOOP_API AMainMenuActor : public AActor
{
	GENERATED_BODY()

public:
	AMainMenuActor();

// ------------------------ Delegate
	UPROPERTY(BlueprintCallable, BlueprintType)
	FOnNewGameButton OnNewGameButton;

	UPROPERTY(BlueprintCallable, BlueprintType)
	FOnContinueButton OnContinueButton;

	UPROPERTY(BlueprintCallable, BlueprintType)
	FOnQuitButton OnQuitButton;

// ------------------------ Event to call bind
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Pull();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Push();

	UFUNCTION(BlueprintImplementableEvent)
	void Quit();
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector StartPullLoc = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector FinalPullLoc = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite)
	float ProgressBar = 0.0f;

	UPROPERTY()
	TWeakObjectPtr<USLHUDWidget> HUDWidget = nullptr;
	
	UPROPERTY()
	TWeakObjectPtr<USLButtonPlay_M> NewGame = nullptr;

	UPROPERTY()
	TWeakObjectPtr<USLButtonContinue_M> Continue = nullptr;

	UPROPERTY(EditAnywhere, Category = "enum | Button")
	EWhichBook Book;

	UFUNCTION(BlueprintCallable)
	USLHUDWidget* CastToHUDWidget();

	UFUNCTION(BlueprintCallable)
	void CastToButton();
};
