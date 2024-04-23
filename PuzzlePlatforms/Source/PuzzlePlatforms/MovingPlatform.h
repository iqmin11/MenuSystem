// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, Category = "Move")
	float Speed = 30.f;

	UPROPERTY(EditAnywhere, Category = "Move", meta = (MakeEditWidget = true))
	FVector TargetLocation;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

private:
	FVector StartWorldLocagtion;
	
	FVector EndWorldLocagtion;

	FVector Dir;

	float JourneyLength;

	UPROPERTY(EditAnywhere)
	int32 ActiveTriggers = 1;

	void CalDir();
};
