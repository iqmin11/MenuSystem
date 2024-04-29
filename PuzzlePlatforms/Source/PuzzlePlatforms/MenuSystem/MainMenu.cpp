// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"

#include "PuzzlePlatforms/PuzzlePlatformGameInstance.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)
	{
		return false;
	}

	// TODO: setup

	if (HostButton == nullptr)
	{
		return false;
	}

	if (JoinButton == nullptr)
	{
		return false;
	}
	
	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostSever);

	return true;
}

void UMainMenu::Setup()
{
	AddToViewport();
	bIsFocusable = true;

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController == nullptr)
	{
		return;
	}

	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* Interface)
{
	MenuInterface = Interface;
}

void UMainMenu::HostSever()
{
	UE_LOG(LogTemp, Warning, TEXT("Host"))
	
	if (MenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail - GameInstance is null"))
		return;
	}

	MenuInterface->Host();
}

void UMainMenu::NativeDestruct()
{
	Super::NativeDestruct();
	RemoveFromViewport();

	UWorld* World = GetWorld();

	if (World == nullptr)
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();

	if (PlayerController == nullptr)
	{
		return;
	}

	PlayerController->bShowMouseCursor = false;

	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	bIsFocusable = false;

	UE_LOG(LogTemp, Warning, TEXT("Menu - Call NativeDestruct"))
}
