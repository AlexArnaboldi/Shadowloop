// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuActor.h"

#include "HUD/SLButtonContinue_M.h"
#include "HUD/SLButtonExit_M.h"
#include "HUD/SLButtonPlay_M.h"
#include "HUD/SLHUDMenu.h"
#include "HUD/SLHUDWidget.h"

AMainMenuActor::AMainMenuActor(): Book()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMainMenuActor::BeginPlay()
{
	Super::BeginPlay();

	StartPullLoc = GetActorLocation();
	
}

USLHUDWidget* AMainMenuActor::CastToHUDWidget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(PlayerController)) { return nullptr; }

	AHUD* HUD = PlayerController->GetHUD();
	if (!IsValid(HUD)) { return nullptr; }

	ASLHUDMenu* HUDMenuRef = Cast<ASLHUDMenu>(HUD);
	if (!IsValid(HUDMenuRef)) { return nullptr; }

	USLHUDWidget* HUDWidgetRef = HUDMenuRef->GetHUDWidget();

	HUDWidget = HUDWidgetRef;
	if (!HUDWidget.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("HUDWidget is invalid"));
		return nullptr;
	}
	
	UE_LOG(LogTemp, Display, TEXT("HUDWidget is valid"));
	
	return HUDWidgetRef;
}

void AMainMenuActor::CastToButton()
{
	switch (Book)
	{
		case EWhichBook::NewGame:
			NewGame = HUDWidget->GetButtonStartLevel();;
			if (NewGame.IsValid())
			{
				NewGame->OnPullBookNewGame.AddDynamic(this, &AMainMenuActor::Pull);
				NewGame->OnPushBookNewGame.AddDynamic(this, &AMainMenuActor::Push);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("AMainMenuActor::ButtonGame is invalid"));
			}
			//UE_LOG(LogTemp, Warning, TEXT("AMainMenuActor::New Game"));
		break;
		
		case EWhichBook::Continue:
			Continue = HUDWidget->GetButtonContinue();
			if (Continue != nullptr)
			{
				Continue->OnPullBookContinue.BindUFunction(this, TEXT("Pull"));
				Continue->OnPushBookContinue.AddDynamic(this, &AMainMenuActor::Push);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AMainMenuActor::Continue is invalid"))
			}
			//UE_LOG(LogTemp, Warning, TEXT("AMainMenuActor::Continue"));
		break;

		case EWhichBook::Quit:
			USLButtonExit_M* Quit = HUDWidget->GetButtonQuit();
			if (Quit != nullptr)
			{
				Quit->OnPullQuit.BindUFunction(this, TEXT("Pull"));
				Quit->OnPushQuit.BindUFunction(this, TEXT("Push"));
				Quit->OnQuit.BindUFunction(this, TEXT("Quit"));
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AMainMenuActor::Quit is invalid"))
			}
		break;
	}
}

