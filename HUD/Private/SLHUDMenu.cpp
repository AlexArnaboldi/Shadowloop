// Fill out your copyright notice in the Description page of Project Settings.
#include "ShadowLoop/Public/HUD/SLHUDMenu.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "ShadowLoop/Public/HUD/SLHUDWidget.h"

void ASLHUDMenu::BeginPlay()
{
	Super::BeginPlay();
	CreateHUDWidget();
}

void ASLHUDMenu::CreateHUDWidget()
{
	ensureMsgf(HUDWidgetClass, TEXT("Invalid widget class in HUD"));
	if (!HUDWidgetClass){return;}
	
	HUDWidget = Cast<USLHUDWidget>(UWidgetBlueprintLibrary::Create(this, HUDWidgetClass, nullptr));

	ensureMsgf(HUDWidget, TEXT("Invalid widget in HUD"));
	if (!HUDWidget){return;}
	
	HUDWidget->AddToViewport(10);
}
