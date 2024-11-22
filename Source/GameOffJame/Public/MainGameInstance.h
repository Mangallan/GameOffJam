// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

class UObjectiveManager;

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMainGameInstance();

protected:

	UPROPERTY(EditAnywhere, Category = Objectives)
	UDataTable* ObjectiveData;
};
