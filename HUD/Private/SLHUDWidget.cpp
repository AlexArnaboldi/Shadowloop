// Fill out your copyright notice in the Description page of Project Settings.
#include "HUD/SLHUDWidget.h"

#include "MainMenuActor.h"
#include "HUD/SLButtonContinue_M.h"
#include "HUD/SLButtonPlay_M.h"
#include "HUD/SLButtonExit_M.h"
#include "Kismet/GameplayStatics.h"

void USLHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ensureMsgf(IsValid(ButtonStartLevel), TEXT("ButtonStartLevel is invalid"));
	if (IsValid(ButtonStartLevel))
	{
		ButtonStartLevel->SetLevelToStart(LevelName);
		ButtonStartLevel->SetHUDWidget(this);
	}

	ensureMsgf(IsValid(ButtonContinue), TEXT("ButtonContinue is invalid"));
	if (IsValid(ButtonContinue))
	{
		ButtonContinue->SetLevelToStart(LevelName);
		ButtonContinue->SetHUDWidget(this);
	}

	GetMainMenuActorRef();
}

void USLHUDWidget::GetMainMenuActorRef()
{
	TArray<AActor*> mainMenuActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMainMenuActor::StaticClass(), mainMenuActors);

	for (AActor* actor : mainMenuActors)
	{
		AMainMenuActor* mainMenuActor = Cast<AMainMenuActor>(actor);
		if (mainMenuActor)
		{
			mainMenuActor->OnNewGameButton.AddDynamic(this, &USLHUDWidget::ButtonNewGameEvent);
			mainMenuActor->OnContinueButton.AddDynamic(this, &USLHUDWidget::ButtonContinueEvent);
			mainMenuActor->OnQuitButton.AddDynamic(this, &USLHUDWidget::ButtonQuitEvent);
		}
	}
}

void USLHUDWidget::CallQuitGame()
{
	if (IsValid(ButtonQuit))
	{
		ButtonQuit->QuitGame();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SLHUDWidget:: ButtonQuit is invalid"));
	}
}

void USLHUDWidget::PlayGame()
{
	ButtonStartLevel->OnClickEvent();
}

void USLHUDWidget::ContinueGame()
{
	ButtonContinue->OnClickEvent();
}
