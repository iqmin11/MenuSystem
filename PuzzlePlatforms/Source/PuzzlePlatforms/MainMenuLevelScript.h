// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenuLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMainMenuLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
};
