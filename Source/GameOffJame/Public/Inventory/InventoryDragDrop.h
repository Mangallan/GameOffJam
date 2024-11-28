// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragDrop.generated.h"

class UInventorySystem;
/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UInventoryDragDrop : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	UInventorySystem* InventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = "true"))
	int Index;
	
	UFUNCTION(BlueprintCallable)
	void HandleItemDropped(int destinationIndex, UInventorySystem* destinationInventory);
};
