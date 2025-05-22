// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLButtonBase.h"
#include "SLButtonContinue_M.generated.h"

class USLHUDWidget;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPullBookContinue);
DECLARE_DYNAMIC_DELEGATE(FOnPullBookContinue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPushBookContinue);

UCLASS()
class SHADOWLOOP_API USLButtonContinue_M : public USLButtonBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UWidgetAnimation> DoorAnimation = nullptr;

	UPROPERTY()
	TWeakObjectPtr<USLHUDWidget> HUDWidget = nullptr;

	FName LevelToStart = NAME_None;

	virtual void NativeConstruct() override;
	
public:
	// ------------------ Delegate ------------------
	FOnPullBookContinue OnPullBookContinue;
	FOnPushBookContinue OnPushBookContinue;

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
