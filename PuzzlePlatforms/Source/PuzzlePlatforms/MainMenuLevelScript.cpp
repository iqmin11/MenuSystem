// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuLevelScript.h"

#include "PuzzlePlatformGameInstance.h"

void AMainMenuLevelScript::BeginPlay()
{
	Super::BeginPlay();

	UPuzzlePlatformGameInstance* GameInst = Cast<UPuzzlePlatformGameInstance>(GetGameInstance());

	if (GameInst == nullptr)
	{
		return;
	}

	GameInst->LoadMenu();

}
