// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLButtonContinue_M.h"
#include "Animation/WidgetAnimation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "HUD/SLHUDWidget.h"

void USLButtonContinue_M::NativeConstruct()
{
	Super::NativeConstruct();

	if (TextBlock)
	{
		TextBlock->SetRenderOpacity(0.f);
	}
}

void USLButtonContinue_M::OnClickEvent()
{
	UGameplayStatics::OpenLevel(this, LevelToStart);
}

void USLButtonContinue_M::ClickButton()
{
	HUDWidget->SoundContinueClick();
}

void USLButtonContinue_M::Hovered()
{
	if (DoorAnimation)
	{
		if (IsAnimationPlaying(DoorAnimation))
		{
			float animationTime = GetAnimationCurrentTime(DoorAnimation);
			PauseAnimation(DoorAnimation);
			
			PlayAnimation(DoorAnimation, animationTime);
		}
		else
		{
			PlayAnimation(DoorAnimation);
		}
	}
	OnPullBookContinue.Execute();
}

void USLButtonContinue_M::Unhovered()
{
	if (DoorAnimation)
	{
		if (IsAnimationPlaying(DoorAnimation))
		{
			float animationTime = DoorAnimation->GetEndTime() - GetAnimationCurrentTime(DoorAnimation);
			PauseAnimation(DoorAnimation);
			
			PlayAnimation(DoorAnimation, animationTime, 1, EUMGSequencePlayMode::Reverse);
		}
		else
		{
			PlayAnimation(DoorAnimation, 0.f, 1, EUMGSequencePlayMode::Reverse);
		}
	}
	OnPushBookContinue.Broadcast();
}

void USLButtonContinue_M::SetLevelToStart(FName InLevelToStart)
{
	LevelToStart = InLevelToStart;
}
