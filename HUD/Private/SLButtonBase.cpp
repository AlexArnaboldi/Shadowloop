// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLButtonBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void USLButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();
	SetText(ButtonText);
}

void USLButtonBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(TextBlock))
	{
		TextBlock->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}

	ensureMsgf(Button, TEXT("Play Button is not valid"));
    if (!Button){return;}
    
    Button->OnClicked.AddDynamic(this, &USLButtonBase::ClickButton);
    Button->OnHovered.AddDynamic(this, &USLButtonBase::Hovered);
    Button->OnUnhovered.AddDynamic(this, &USLButtonBase::Unhovered);
}

void USLButtonBase::SetText(const FText& InText)
{
	if (!TextBlock){return;}
	TextBlock->SetText(InText);
}

void USLButtonBase::ClickButton()
{
	//Mouse click on
}

void USLButtonBase::Hovered()
{
	//Mouse goes on the button
}

void USLButtonBase::Unhovered()
{
	//Mouse leaves the button
}
