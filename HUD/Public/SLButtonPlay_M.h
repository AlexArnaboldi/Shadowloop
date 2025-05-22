// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SLButtonBase.h"
#include "SLButtonPlay_M.generated.h"

class USLHUDWidget;
class AMainMenuActor;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPullBookNewGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPushBookNewGame);

UCLASS()
class SHADOWLOOP_API USLButtonPlay_M : public USLButtonBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	FWidgetTransform TextLocation;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UWidgetAnimation> DoorAnimation = nullptr;

	UPROPERTY()
	TWeakObjectPtr<USLHUDWidget> HUDWidget = nullptr;

	FName LevelToStart = NAME_None;
	
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
public:

	// ------------------ Delegate ------------------
	FOnPullBookNewGame OnPullBookNewGame;
	FOnPushBookNewGame OnPushBookNewGame;

	void SetHUDWidget(USLHUDWidget* InHUDWidget){ HUDWidget = InHUDWidget; };
	void OnClickEvent();
	
	UFUNCTION()
	virtual void ClickButton() override;

	UFUNCTION(BlueprintCallable)
	virtual void Hovered() override;

	UFUNCTION(BlueprintCallable)
	virtual void Unhovered() override;

	void SetLevelToStart(FName InLevelToStart);
};
