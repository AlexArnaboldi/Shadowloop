// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLButtonExit_M.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"

void USLButtonExit_M::NativeConstruct()
{
	Super::NativeConstruct();

}

void USLButtonExit_M::ClickButton()
{
	OnQuit.Execute();
}

void USLButtonExit_M::Hovered()
{
	OnPullQuit.Execute();
}

void USLButtonExit_M::Unhovered()
{
	OnPushQuit.Execute();
}

void USLButtonExit_M::QuitGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
