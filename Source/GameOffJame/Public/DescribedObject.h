// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DescribedObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDescribedObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEOFFJAME_API IDescribedObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Description")
	FText GetDisplayName();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Description")
	FText GetDescription();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Description")
	FText GetActionDescription();
};
