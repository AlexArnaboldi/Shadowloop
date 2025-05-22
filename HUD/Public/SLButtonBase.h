// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "SLButtonBase.generated.h"


class UTextBlock;
class UButton;

UCLASS()
class SHADOWLOOP_API USLButtonBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category="Game Button Base | Config")
	FText ButtonText;
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> Button = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TextBlock = nullptr;
	
public:
	void SetText(const FText& InText);
	
	virtual void ClickButton();
	virtual void Hovered();
	virtual void Unhovered();
};
