// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "StaticFunctions.generated.h"

class UInputAction;

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UStaticFunctions : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category = Input)
	static FText GetActionActiveKeyBind(const FName actionName);
};
