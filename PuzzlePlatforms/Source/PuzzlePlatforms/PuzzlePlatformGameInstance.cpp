// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformGameInstance.h"

#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformGameInstance::UPuzzlePlatformGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Constructor"))

	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	MenuClass = MenuBPClass.Class;
}

void UPuzzlePlatformGameInstance::Init()
{
	Super::Init();

	if (MenuClass == nullptr)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *MenuClass->GetName())
}

void UPuzzlePlatformGameInstance::LoadMenu()
{
	if (MenuClass == nullptr)
	{
		return;
	}

	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (Menu == nullptr)
	{
		return;
	}

	Menu->Setup();
	Menu->SetMenuInterface(this);

}

void UPuzzlePlatformGameInstance::Host()
{
	UEngine* Engine = GEngine;

	if (!ensure(Engine != nullptr))
	{
		return;
	}

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr))
	{
		return;
	}

	World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GEngine;
		
	if (!ensure(Engine != nullptr))
	{
		return;
	}

	Engine->AddOnScreenDebugMessage(0, 2.f, FColor::Green, FString::Printf(TEXT("Joining : %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController != nullptr))
	{	
		return;
	}

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
