// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "SLPageBase.h"
#include "SLPageGameOver.generated.h"

class UImage;
class UTextBlock;
class USLButtonRestart_GO;
class USLButtonMainMenu_GO;

UCLASS()
class SHADOWLOOP_API USLPageGameOver : public USLPageBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName LevelRestartName = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName MainMenuName = NAME_None;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USLButtonMainMenu_GO> ButtonMainMenu = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<USLButtonRestart_GO> ButtonRestart = nullptr;

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//TObjectPtr<UTextBlock> TextGameOver = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> GameOverImage = nullptr;
	
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	void SetPlayerInput();
	UFUNCTION(BlueprintCallable)
	void SetMouseConfig();

	UFUNCTION(BlueprintCallable)
	void ActiveButtons();
};
