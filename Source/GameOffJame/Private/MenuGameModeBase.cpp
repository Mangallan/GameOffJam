// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameModeBase.h"

#include "Blueprint/UserWidget.h"

void AMenuGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (IsValid(WidgetClass) && World)
	{
		UserWidget = CreateWidget(World, WidgetClass);

		if (UserWidget)
		{
			UserWidget->AddToViewport();

			PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->SetShowMouseCursor(true);
				PlayerController->SetInputMode(FInputModeUIOnly());
			}
		}
	}
}

void AMenuGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	UWorld* World = GetWorld();
	if (World)
	{
		if (PlayerController)
		{
			PlayerController->SetShowMouseCursor(false);
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}
