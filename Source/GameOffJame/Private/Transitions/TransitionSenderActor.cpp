// Fill out your copyright notice in the Description page of Project Settings.


#include "Transitions/TransitionSenderActor.h"
#include "MainGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "MainCharacter.h"
#include "Components/SphereComponent.h"

ATransitionSenderActor::ATransitionSenderActor()
{
	_triggerComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
	SetRootComponent(_triggerComponent);
}

void ATransitionSenderActor::SendTransition(TSubclassOf<UUserWidget> loadingScreenWidget)
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

	gameManager->CurrentTransitionId = _transitionId;

	if (IsValid(loadingScreenWidget))
	{
		UUserWidget* userWidget = CreateWidget(world, loadingScreenWidget);

		if (userWidget)
		{
			userWidget->AddToViewport();

			APlayerController* playerController = world->GetFirstPlayerController();
			if (playerController)
			{
				playerController->DisableInput(playerController);
			}

			world->GetTimerManager().SetTimer(_timerHandle, this, &ATransitionSenderActor::LoadLevel, 0.25f, false);
		}
	}
	else
	{
		LoadLevel();
	}
}

void ATransitionSenderActor::BeginPlay()
{
	Super::BeginPlay();

	if (_triggerComponent && _loadingScreen)
	{
		_triggerComponent->OnComponentBeginOverlap.AddDynamic(this, &ATransitionSenderActor::OnObjectOverlap);
	}
}

void ATransitionSenderActor::LoadLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), _targetLevelName);
}

void ATransitionSenderActor::OnObjectOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	AMainCharacter* character = Cast<AMainCharacter>(otherActor);
	if (character)
	{
		SendTransition(_loadingScreen);
	}
}

