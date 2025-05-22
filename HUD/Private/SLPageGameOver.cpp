// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLPageGameOver.h"
#include "HUD/SLButtonMainMenu_GO.h"
#include "HUD/SLButtonRestart_GO.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USLPageGameOver::NativeConstruct()
{
	Super::NativeConstruct();

	ButtonMainMenu->SetVisibility(ESlateVisibility::Hidden);
	ButtonRestart->SetVisibility(ESlateVisibility::Hidden);
	GameOverImage->SetVisibility(ESlateVisibility::Hidden);

	SetPlayerInput();
}

void USLPageGameOver::NativeDestruct()
{
	Super::NativeDestruct();
}

void USLPageGameOver::SetPlayerInput()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();

	ensureMsgf(Player, TEXT("Player not found in GameOver PlayerInput"));
	if (!Player){return;}
	
	Player->SetIgnoreLookInput(true);
	Player->SetIgnoreMoveInput(true);
	
// ---- Choose InputMode UIOnly/GameOnly
	Player->SetInputMode(FInputModeUIOnly());
}

void USLPageGameOver::SetMouseConfig()
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();

	ensureMsgf(Player, TEXT("Player not found in GameOver MouseConf"));
	if (!Player){return;}
	
	int32 SizeX = 0;
	int32 SizeY = 0;

	Player->SetShowMouseCursor(true);
	Player->GetViewportSize(SizeX, SizeY);
	Player->SetMouseLocation(SizeX/2, SizeY/2);	
}

void USLPageGameOver::ActiveButtons()
{
	if (!IsValid(ButtonMainMenu))
	{
		UE_LOG(LogTemp, Error, TEXT("ButtonMainMenu is invalid"));
	}
	else
	{
		ButtonMainMenu->SetVisibility(ESlateVisibility::Visible);
		ButtonMainMenu->SetLevelMenuName(MainMenuName);
	}

	if (!IsValid(ButtonRestart))
	{
		UE_LOG(LogTemp, Error, TEXT("ButtonRestart is invalid"));
	}
	else
	{
		ButtonRestart->SetVisibility(ESlateVisibility::Visible);
		ButtonRestart->SetRestartLevelName(LevelRestartName);
	}

	if (!IsValid(GameOverImage))
	{
		UE_LOG(LogTemp, Error, TEXT("ButtonRestart is invalid"));
	}
	else
	{
		GameOverImage->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
}
