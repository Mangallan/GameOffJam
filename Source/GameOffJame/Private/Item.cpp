// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Interactable.h"
#include "Inventory/InventorySystem.h"

// Sets default values for this component's properties
UItem::UItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UItem::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UItem::PickupItem(AActor* interactor)
{
	UInventorySystem* inventory = interactor->GetComponentByClass<UInventorySystem>();

	if (inventory == nullptr || ItemId.DataTable == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0F, FColor::Emerald, TEXT("1"));
		return;
	}

	const FString& contextString = TEXT("test");
	FItemData* data = ItemId.GetRow<FItemData>(contextString);

	if (data)
	{
		bool isSuccessful;
		int quantityRemaining;
		inventory->AddToInventory(ItemId.RowName, _quantity, isSuccessful, quantityRemaining);

		if (isSuccessful)
		{
			UInteractable* interactable = GetOwner()->GetComponentByClass<UInteractable>();
			if (interactable)
			{
				interactable->UnBindFunctions();
			}
			GetOwner()->Destroy();
		}
	}
}

