// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveGame/SLSaveGame.h"


USLSaveGame::USLSaveGame()
{
	SaveSlotName = "Test save slot";
	StartPlayerLoc = FVector(0.f, 0.f, 0.f);
	CurrentLevel = 0;
}
