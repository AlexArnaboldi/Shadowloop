// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Blueprint/UserWidget.h"
#include "SLHUDWidget.generated.h"

class USLButtonBase;
class AMainMenuActor;
class USLButtonContinue_M;
class USLButtonPlay_M;
class USLButtonExit_M;

UCLASS()
class SHADOWLOOP_API USLHUDWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName LevelName = NAME_None;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<USLButtonPlay_M> ButtonStartLevel = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<USLButtonContinue_M> ButtonContinue = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<USLButtonExit_M> ButtonQuit = nullptr;
	
	virtual void NativeConstruct() override;

	void GetMainMenuActorRef();

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonNewGameEvent(float InProgressBar);

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonContinueEvent(float InProgressBar);

	UFUNCTION(BlueprintImplementableEvent)
	void ButtonQuitEvent();

	UFUNCTION(BlueprintCallable)
	void CallQuitGame();

	UFUNCTION(BlueprintCallable)
	void PlayGame();
	UFUNCTION(BlueprintCallable)
	void ContinueGame();
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void SoundPlayClick();

	UFUNCTION(BlueprintImplementableEvent)
	void SoundContinueClick();
	
	USLButtonPlay_M* GetButtonStartLevel(){ return ButtonStartLevel; }
	USLButtonContinue_M* GetButtonContinue(){ return ButtonContinue; }
	USLButtonExit_M* GetButtonQuit(){ return ButtonQuit; }
};
