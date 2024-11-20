// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UGameManager : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleInstanceOnly, Category = "Transitions")
	FString CurrentTransitionId;
};
