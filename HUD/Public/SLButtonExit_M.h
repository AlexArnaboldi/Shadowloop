// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SLButtonBase.h"
#include "SLButtonExit_M.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnPullQuit);
DECLARE_DYNAMIC_DELEGATE(FOnPushQuit);
DECLARE_DYNAMIC_DELEGATE(FOnQuit);

UCLASS()
class SHADOWLOOP_API USLButtonExit_M : public USLButtonBase
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
public:
// -------------------- Delegate
	FOnPullQuit OnPullQuit;
	FOnPushQuit OnPushQuit;
	FOnQuit OnQuit;
	
	UFUNCTION()
	virtual void ClickButton();

	UFUNCTION()
	virtual void Hovered();

	UFUNCTION()
	virtual void Unhovered();

	void QuitGame();
};
