// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "GameFramework/HUD.h"
#include "SLHUDMenu.generated.h"

class USLHUDWidget;

UCLASS()
class SHADOWLOOP_API ASLHUDMenu : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<USLHUDWidget> HUDWidgetClass = nullptr;

protected:
	virtual void BeginPlay() override;
	
private:
	TObjectPtr<USLHUDWidget> HUDWidget = nullptr;
private:
	void CreateHUDWidget();
public:
	UFUNCTION(BlueprintCallable)
	USLHUDWidget* GetHUDWidget(){ return HUDWidget; }
};
