// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventorySystem.h"

#include "Camera/PlayerCameraManager.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/UserWidget.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	_isInventoryOpened = false;
}


// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
	LoadInventory();
}

void UInventorySystem::AddToInventory(FName itemId, int quantity, bool& isSuccessful, int& quantityRemaining)
{
	quantityRemaining = quantity;
	isSuccessful = true;

	while (quantityRemaining > 0 && isSuccessful)
	{
		int index;
		bool hasFoundSlot;
		int slotQuantityLeft;
		FindSlot(itemId, hasFoundSlot, index, slotQuantityLeft);

		if (hasFoundSlot)
		{
			int quantityToAdd = FMath::Min(quantityRemaining, slotQuantityLeft);
			AddToStack(index, quantityToAdd);

			quantityRemaining -= quantityToAdd;
		}
		else
		{
			if (CreateNewStack(itemId, 1))
			{
				quantityRemaining--;
			}
			else
			{
				isSuccessful = false;
			}
		}
	}

	quantityRemaining = FMath::Max(quantityRemaining, 0);
	Update();
}

void UInventorySystem::RemoveFromInventory(int index, bool removeAll, bool isConsumed)
{
	FSlotData data = Content[index];

	if (data.Quantity == 1 || removeAll)
	{
		Content[index].ItemId = FName();
		Content[index].Quantity = 0;

		if (isConsumed)
		{

		}
		else
		{
			DropItem(data.ItemId, data.Quantity);
		}
	}
	else
	{
		Content[index].Quantity--;

		if (isConsumed)
		{

		}
		else
		{
			DropItem(data.ItemId, 1);
		}
	}
}

void UInventorySystem::QueryInventory(FName itemId, int quantity, bool& found)
{
	int runningTotal{};
	for (FSlotData data : Content)
	{
		if (itemId == data.ItemId)
		{
			runningTotal += data.Quantity;
		}
	}

	found = runningTotal >= quantity;
	if (found)
	{
		// Return wanted queries.
	}
}

void UInventorySystem::ToggleInventory()
{
	_isInventoryOpened = !_isInventoryOpened;
	InventoryPressedEvent.Broadcast(_isInventoryOpened);
}

void UInventorySystem::TransferSlots(int sourceIndex, UInventorySystem* sourceComponent, int destinationIndex)
{
	FSlotData transferringData = sourceComponent->Content[sourceIndex];

	if (destinationIndex < 0)
	{
	}
	else
	{
		if (transferringData.ItemId == Content[destinationIndex].ItemId)
		{
			int totalQuantity = transferringData.Quantity + Content[destinationIndex].Quantity;
			int destinationQuantity = FMath::Min(totalQuantity, GetMaxStackSize(transferringData.ItemId));
			int sourceQuantity = totalQuantity - destinationQuantity;

			sourceComponent->Content[sourceIndex].Quantity = sourceQuantity;
			Content[destinationIndex].Quantity = destinationQuantity;
		}
		else
		{
			sourceComponent->Content[sourceIndex] = Content[destinationIndex];
			Content[destinationIndex] = transferringData;
		}

		sourceComponent->InventoryUpdatedEvent.Broadcast();
		Update();
	}
}

void UInventorySystem::Update()
{
	InventoryUpdatedEvent.Broadcast();
	SaveInventory();
}

void UInventorySystem::FindSlot(FName itemId, bool& hasFoundSlot, int& index, int& slotRemainingQuantity)
{
	slotRemainingQuantity = -1;
	index = -1;
	hasFoundSlot = false;

	for (int i = 0; i < Content.Num(); i++)
	{
		FSlotData data = Content[i];
		if (data.ItemId == itemId && data.Quantity < GetMaxStackSize(itemId))
		{
			index = i;
			hasFoundSlot = true;
			slotRemainingQuantity = GetMaxStackSize(itemId) - data.Quantity;

			return;
		}
	}
}

int UInventorySystem::GetMaxStackSize(FName itemId)
{
	if (_itemsDataTable)
	{
		const FString& context = TEXT("Context");
		FItemData* data = _itemsDataTable->FindRow<FItemData>(itemId, context);

		if (data)
		{
			return data->StackSize;
		}
	}

	return -1;
}

void UInventorySystem::AddToStack(int index, int quantity)
{
	if (index < 0 || index >= Content.Num())
	{
		return;
	}

	Content[index].Quantity += quantity;
}

int UInventorySystem::GetAvailableEmptySlot()
{
	for (int i = 0; i < Content.Num(); i++)
	{
		if (Content[i].Quantity == 0)
		{
			return i;
		}
	}

	return -1;
}

bool UInventorySystem::CreateNewStack(FName itemId, int quantity)
{
	int index = GetAvailableEmptySlot();
	if (index >= 0)
	{
		Content[index].ItemId = itemId;
		Content[index].Quantity = quantity;

		return true;
	}

	return false;
}

void UInventorySystem::DropItem(FName itemId, int quantity)
{
	FItemData data = GetItemData(itemId);
	
	for (int i = 0; i < quantity; i++)
	{
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;

		AActor* item = GetWorld()->SpawnActor<AActor>(data.ItemClass, GetDropLocation(), Rotation, SpawnInfo);
	}

	Update();
}

FItemData UInventorySystem::GetItemData(FName itemId)
{
	if (_itemsDataTable)
	{
		const FString& context = TEXT("Context");
		FItemData* data = _itemsDataTable->FindRow<FItemData>(itemId, context);

		if (data)
		{
			return *data;
		}
	}

	return FItemData();
}

FVector UInventorySystem::GetDropLocation()
{
	FVector actorLocation = GetOwner()->GetActorLocation();

	FVector forwardLocation = GetOwner()->GetActorForwardVector();
	return actorLocation + forwardLocation;
}

void UInventorySystem::SaveInventory()
{
	UMainGameInstance* gameManager = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameManager == nullptr)
	{
		return;
	}

	gameManager->InventoryContent = Content;
}

void UInventorySystem::LoadInventory()
{
	UMainGameInstance* gameManager = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (gameManager == nullptr)
	{
		return;
	}

	TArray<FSlotData> loadedContent = gameManager->InventoryContent;
	if (loadedContent.Num() == 0)
	{
		Content.SetNum(_inventorySize);
	}
	else
	{
		Content = loadedContent;
	}
}

