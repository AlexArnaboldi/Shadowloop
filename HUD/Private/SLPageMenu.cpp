// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLPageMenu.h"

#include "HUD/SLButtonMainMenu_G.h"
#include "HUD/SLButtonReturnPlay_G.h"


void USLPageMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuButton != nullptr)
	{
		MainMenuButton->SetMainMenuLevelName(MainMenuLevelName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MainMenuButton is NULL"));
	}
		
	
	bIsMenuInput = true;
	SetMouseAndInputForMenu(bIsMenuInput);
	GetWorld()->GetWorldSettings()->SetTimeDilation(0.f);
}

void USLPageMenu::NativeDestruct()
{
	Super::NativeDestruct();

	bIsMenuInput = false;
	SetMouseAndInputForMenu(bIsMenuInput);
	GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);
}

void USLPageMenu::SetMouseAndInputForMenu(bool InMenuInput)
{
	APlayerController* Player = GetWorld()->GetFirstPlayerController();

	int32 SizeX = 0;
	int32 SizeY = 0;

	ensureMsgf(Player, TEXT("Player not found in Pause Menu"));
	if (!Player){return;}
	
	Player->SetShowMouseCursor(InMenuInput);
	
	Player->SetIgnoreLookInput(InMenuInput);
	Player->SetIgnoreMoveInput(InMenuInput);
	

	if (InMenuInput)
	{
// ------------------- In Construct
		//Mouse set position
		Player->GetViewportSize(SizeX, SizeY);
		Player->SetMouseLocation(SizeX/2, SizeY/2);
		
		Player->SetInputMode(FInputModeGameAndUI());
	}
	else
	{
// ------------------- In Destruct
		Player->SetInputMode(FInputModeGameOnly());
	}
}
