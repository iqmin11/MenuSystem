// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartWorldLocagtion = GetActorLocation();
	EndWorldLocagtion = GetTransform().TransformPosition(TargetLocation);
	CalDir();
	JourneyLength = (EndWorldLocagtion - StartWorldLocagtion).Size();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActiveTriggers > 0)
	{
		if (HasAuthority())
		{
			FVector CurLocation = GetActorLocation();

			float JourneyTravelled = (CurLocation - StartWorldLocagtion).Size();

			if (JourneyLength < JourneyTravelled)
			{
				std::swap(StartWorldLocagtion, EndWorldLocagtion);
				CalDir();
			}

			CurLocation += Dir * Speed * DeltaTime;
			SetActorLocation(CurLocation);
		}
	}
}

void AMovingPlatform::AddActiveTrigger()
{
	++ActiveTriggers;
}

void AMovingPlatform::RemoveActiveTrigger()
{
	if (ActiveTriggers > 0)
	{
		--ActiveTriggers;
	}
}

void AMovingPlatform::CalDir()
{
	Dir = (EndWorldLocagtion - StartWorldLocagtion).GetSafeNormal();
}