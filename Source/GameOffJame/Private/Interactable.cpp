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
	if (setInteracting && CanInteract())
	{
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
		GetWorld()->GetTimerManager().ClearTimer(InteractTimerHandle);
	}

	IsInteracting = setInteracting;
}

void UInteractable::BindSetInteractFunction(UObject* bindee, FName functionName)
{
	SetInteractBinding.BindUFunction(bindee, functionName);
}

void UInteractable::BindCanInteractFunction(UObject* bindee, FName functionName)
{
	CanInteractBinding.BindUFunction(bindee, functionName);
}

void UInteractable::BindInteractionCompleteFunction(UObject* bindee, FName functionName)
{
	CompleteInteractBinding.BindUFunction(bindee, functionName);
}

bool UInteractable::CanInteract()
{
	bool result = true;

	if (CanInteractBinding.IsBound())
	{
		result = CanInteractBinding.Execute();
	}

	return result;
}

float UInteractable::GetInteractionElapsedTime()
{
	return GetWorld()->GetTimerManager().GetTimerElapsed(InteractTimerHandle);
}

void UInteractable::InteractionComplete()
{
	if (CompleteInteractBinding.IsBound())
	{
		CompleteInteractBinding.Execute();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Interaction complete but no overriden behavior"))
	}

	SetInteract(nullptr, false); // Reset interact state
}