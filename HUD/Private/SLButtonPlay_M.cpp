// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SLButtonPlay_M.h"

#include "Animation/WidgetAnimation.h"
#include "Components/TextBlock.h"
#include "HUD/SLHUDWidget.h"
#include "Kismet/GameplayStatics.h"

void USLButtonPlay_M::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TextBlock)
	{
		TextBlock->SetRenderTransform(TextLocation);
	}
}

void USLButtonPlay_M::NativeConstruct()
{
	Super::NativeConstruct();

	if (TextBlock)
	{
		TextBlock->SetRenderOpacity(0.f);
	}
	
}

void USLButtonPlay_M::OnClickEvent()
{
	if (UGameplayStatics::DoesSaveGameExist("SaveOneSlot", 0))
    	{
    		UGameplayStatics::DeleteGameInSlot("SaveOneSlot", 0);
    	}
    	
    	UGameplayStatics::OpenLevel(this, LevelToStart);
}

void USLButtonPlay_M::ClickButton()
{
	HUDWidget->SoundPlayClick();
}

void USLButtonPlay_M::Hovered()
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

	OnPullBookNewGame.Broadcast();
}

void USLButtonPlay_M::Unhovered()
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

	OnPushBookNewGame.Broadcast();
}

void USLButtonPlay_M::SetLevelToStart(FName InLevelToStart)
{
	LevelToStart = InLevelToStart; 
}


