// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Widget.h"
#include "Components/EditableText.h"

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

	HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostSever);

	if (JoinButton == nullptr)
	{
		return false;
	}
	
	JoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (CancelButton == nullptr)
	{
		return false;
	}

	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (ConnectGameButton == nullptr)
	{
		return false;
	}

	ConnectGameButton->OnClicked.AddDynamic(this, &UMainMenu::JoinSever);

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

void UMainMenu::JoinSever()
{
	if (MenuInterface == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fail - GameInstance is null"))
		return;
	}

	if (IPAddressField == nullptr)
	{
		return;
	}
	
	const FString& IP = IPAddressField->GetText().ToString();

	MenuInterface->Join(IP);
}

void UMainMenu::OpenJoinMenu()
{
	if (MenuSwitcher == nullptr)
	{
		return;
	}

	if (JoinMenu == nullptr)
	{
		return;
	}

	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	if (MenuSwitcher == nullptr)
	{
		return;
	}

	if (MainMenu == nullptr)
	{
		return;
	}

	MenuSwitcher->SetActiveWidget(MainMenu);
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
