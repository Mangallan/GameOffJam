// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractorComponent.h"

#include "Interactable.h"
#include "Components\ShapeComponent.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UInteractorComponent::RegisterInteractVolume(UShapeComponent* interactorVolume)
{
	interactorVolume->OnComponentBeginOverlap.AddDynamic(this, &UInteractorComponent::OnOverlap);
	interactorVolume->OnComponentEndOverlap.AddDynamic(this, &UInteractorComponent::OnOverlapEnd);
}

void UInteractorComponent::OnOverlap(
	UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& sweepResult)
{
	if (otherActor->Implements<UInteractable>())
	{
		OverlappedInteractable = otherActor;
	}
}

void UInteractorComponent::OnOverlapEnd(
	UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex)
{
	if (otherActor == OverlappedInteractable)
	{
		OverlappedInteractable = nullptr;
	}
}

bool UInteractorComponent::SetInteract(bool interacting)
{
	bool result = false;

	if (OverlappedInteractable && OverlappedInteractable->Implements<UInteractable>() && IInteractable::Execute_CanInteract(OverlappedInteractable, this->GetOwner()))
	{
		IInteractable::Execute_SetInteract(OverlappedInteractable, this->GetOwner(), interacting);
	}

	return result;
}