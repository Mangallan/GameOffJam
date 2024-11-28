// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"


USTRUCT(BlueprintType)
struct GAMEOFFJAME_API FSlotData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	FName ItemId = "None";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	int Quantity{};
};

USTRUCT(BlueprintType)
struct GAMEOFFJAME_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Thumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int StackSize;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFFJAME_API UInventorySystem : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventorySystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FSlotData> Content;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryPressed, bool, isOpened);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryUpdated);

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FInventoryPressed InventoryPressedEvent;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FInventoryUpdated InventoryUpdatedEvent;

	UFUNCTION(BlueprintCallable)
	void AddToInventory(FName itemId, int quantity, bool& isSuccessful, int& quantityRemaining);

	UFUNCTION(BlueprintCallable)
	void RemoveFromInventory(int index, bool removeAll, bool isConsumed);

	UFUNCTION(BlueprintPure)
	void QueryInventory(FName itemId, int quantity, bool& found);

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();

	UFUNCTION(BlueprintCallable)
	void TransferSlots(int sourceIndex, UInventorySystem* sourceComponent, int destinationIndex);

	void Update();

private:
	UPROPERTY(EditAnywhere)
	int _inventorySize = 16;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* _itemsDataTable;

	bool _isInventoryOpened;

	void FindSlot(FName itemId, bool& hasFoundSlot, int& index, int& slotRemainingQuantity);

	UFUNCTION(BlueprintPure)
	int GetMaxStackSize(FName itemId);

	void AddToStack(int index, int quantity);

	UFUNCTION(BlueprintPure)
	int GetAvailableEmptySlot();
		
	bool CreateNewStack(FName itemId, int quantity);

	void DropItem(FName itemId, int quantity);

	FItemData GetItemData(FName itemId);

	FVector GetDropLocation();

	void SaveInventory();
	void LoadInventory();
};
