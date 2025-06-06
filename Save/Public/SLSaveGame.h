﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SLSaveGame.generated.h"

UCLASS()
class SHADOWLOOP_API USLSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FVector StartPlayerLoc = FVector::ZeroVector;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	int CurrentLevel = 0;
	
	USLSaveGame();
};
