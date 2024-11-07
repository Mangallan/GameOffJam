// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Controllable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UControllable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Specifies this object can have controls sent to it by sources such as AInputController
 */
class GAMEOFFJAME_API IControllable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	// 2D plane constrained movement control
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controls")
	void Move(FVector2D input);

	// 2D rotation constrained view control
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controls")
	void Look(FVector2D input);

	// Button controlled "rise" i.e. jump, float
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controls")
	void Rise(bool isPressed);

	// Button controlled "fall" i.e. crouch, descend
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controls")
	void Fall(bool isPressed);

	// Interact with control, can be overriden but defaults to calling Interact on a UInteractorComponent
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Controls")
	void Interact(bool isPressed);

};
