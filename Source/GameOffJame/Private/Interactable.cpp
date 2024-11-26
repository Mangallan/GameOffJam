// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactable.h"

void UInteractable::SetInteract(AActor* interactor, bool setInteracting)
{
	if (SetInteractBinding.IsBound())
	{
		SetInteractBinding.Execute(interactor, setInteracting);
	}
	else
	{
		SetInteractDefault(interactor, setInteracting);
	}
}

void UInteractable::SetInteractDefault(AActor* interactor, bool setInteracting)
{
	if (setInteracting && CanInteract(interactor))
	{
		ActiveInteractor = interactor;

		if (InteractionRequiresHold)
		{
			if (InteractionTimeRequired <= 0.0f) { UE_LOG(LogTemp, Warning, TEXT("Time is not set for held interaction!")) }

			GetWorld()->GetTimerManager().SetTimer(InteractTimerHandle, this, &UInteractable::InteractionComplete, InteractionTimeRequired);
		}
		else
		{
			InteractionComplete();
		}
	}	
	else
	{
		ActiveInteractor = nullptr;
		GetWorld()->GetTimerManager().ClearTimer(InteractTimerHandle);
	}

	IsInteracting = setInteracting;
}

void UInteractable::BindSetInteractFunction(FSetInteractDelegate function)
{
	SetInteractBinding = function;
}

void UInteractable::BindCanInteractFunction(FCanInteractDelegate function)
{
	CanInteractBinding = function;
}

void UInteractable::BindInteractionCompleteFunctionToMulticast(FInteractionCompleteDelegate function)
{
	CompleteInteractMulticast.Add(function);
}

bool UInteractable::CanInteract(AActor* interactor)
{
	bool result = true;

	if (CanInteractBinding.IsBound())
	{
		result = CanInteractBinding.Execute(interactor);
	}

	return result;
}

float UInteractable::GetInteractionElapsedTime()
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(InteractTimerHandle);
}

void UInteractable::InteractionComplete()
{
	if (CompleteInteractMulticast.IsBound())
	{
		CompleteInteractMulticast.Broadcast(ActiveInteractor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction complete but no overriden behavior"))
	}

	SetInteract(nullptr, false); // Reset interact state
}

void UInteractable::UnBindFunctions()
{
	SetInteractBinding.Unbind();
	CanInteractBinding.Unbind();
}
