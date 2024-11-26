// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interactable.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEOFFJAME_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool InteractionRequiresHold = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess="true"))
	float InteractionTimeRequired = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	bool IsInteracting = false;

	AActor* ActiveInteractor;

	FTimerHandle InteractTimerHandle;

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FSetInteractDelegate, AActor*, interactor, bool, setInteract);
	DECLARE_DYNAMIC_DELEGATE_RetVal_OneParam(bool, FCanInteractDelegate, AActor*, interactor);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FInteractionCompleteDelegate, AActor*, interactor);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractionCompleteEvent, AActor*, interactor);

	FSetInteractDelegate SetInteractBinding;
	FCanInteractDelegate CanInteractBinding;
	FInteractionCompleteEvent CompleteInteractMulticast;

public:

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void BindSetInteractFunction(FSetInteractDelegate function);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteract(AActor* interactor, bool setInteracting);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void SetInteractDefault(AActor* interactor, bool setInteracting);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void BindCanInteractFunction(FCanInteractDelegate function);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool CanInteract(AActor* interactor);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	float GetInteractionElapsedTime();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void BindInteractionCompleteFunctionToMulticast(FInteractionCompleteDelegate function);

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void InteractionComplete();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void UnBindFunctions();
};
