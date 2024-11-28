// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayMode.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Transitions/TransitionReceiverActor.h"

#include "MainCharacter.h"

void AGameplayMode::BeginPlay()
{
	UWorld* world = GetWorld();

	if (!world)
	{
		return;
	}

	UMainGameInstance* gameManager = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(world));

	if (!gameManager)
	{
		return;
	}


	MoveToTransitionPoint(gameManager->CurrentTransitionId, world);
}

void AGameplayMode::MoveToTransitionPoint(const FString transitionId, const UWorld* world)
{
	APlayerController* playerController = world->GetFirstPlayerController();
	if (playerController)
	{
		playerController->EnableInput(playerController);
	}

	if (transitionId.Equals("") || world == nullptr)
	{
		return;
	}

	for (TActorIterator<ATransitionReceiverActor> actorIter(world); actorIter; ++actorIter)
	{
		if (transitionId.Equals(actorIter->GetTransitionId()))
		{
			FVector target = actorIter->GetActorLocation();
			FRotator rotation = actorIter->GetActorRotation();

			for (TActorIterator<AMainCharacter> characterIter(world); characterIter; ++characterIter)
			{
				if (characterIter && characterIter->IsPlayerControlled())
				{
					characterIter->SetActorLocationAndRotation(target, rotation);
					break;
				}
			}

			break;
		}
	}
}
