// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLPageBase.h"
#include "SLPageMenu.generated.h"

class USLButtonMainMenu_G;
class ACustomPlayer;

UCLASS()
class SHADOWLOOP_API USLPageMenu : public USLPageBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MainMenuLevelName = NAME_None;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USLButtonMainMenu_G> MainMenuButton = nullptr;
 	
	bool bIsMenuInput = false;
	
	virtual void NativeConstruct() override;
	
	virtual void NativeDestruct() override;

	void SetMouseAndInputForMenu(bool bEnable);
};
