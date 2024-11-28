// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameplayMode.generated.h"

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API AGameplayMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	void MoveToTransitionPoint(const FString transitionId, const UWorld* world);
};
