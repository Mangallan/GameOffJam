// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryDragDrop.h"
#include "Inventory/InventorySystem.h"

void UInventoryDragDrop::HandleItemDropped(int destinationIndex, UInventorySystem* destinationInventory)
{
	if (destinationIndex != Index || destinationInventory != InventoryComponent)
	{
		InventoryComponent->TransferSlots(destinationIndex, destinationInventory, Index);
	}
}
