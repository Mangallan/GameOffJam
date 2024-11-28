// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"

#include "Inventory/InventorySystem.h"

#include "MainGameInstance.generated.h"

class UObjectiveManager;

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

	UPROPERTY(VisibleAnywhere, Category = "Transitions")
	FString CurrentTransitionId;

	UPROPERTY(VisibleAnywhere, Category = "Inventory System")
	TArray<FSlotData> InventoryContent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory System")
	TArray<int> HotbarContent;

	UPROPERTY(EditAnywhere, Category = "Inventory System")
	UDataTable* ItemsData;

protected:

	UPROPERTY(EditAnywhere, Category = Objectives)
	UDataTable* ObjectiveData;
};
