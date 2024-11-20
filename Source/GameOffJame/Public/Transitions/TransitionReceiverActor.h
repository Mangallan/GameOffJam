// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransitionReceiverActor.generated.h"

UCLASS()
class GAMEOFFJAME_API ATransitionReceiverActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATransitionReceiverActor();

	FString GetTransitionId() const { return _transitionId; }

private:
	UPROPERTY(EditAnywhere, Category = "Transition Settings", meta = (AllowPrivateAccess = "true"))
	FString _transitionId;

};
