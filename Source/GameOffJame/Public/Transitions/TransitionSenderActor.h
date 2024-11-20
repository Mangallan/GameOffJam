// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TransitionSenderActor.generated.h"

UCLASS()
class GAMEOFFJAME_API ATransitionSenderActor : public AActor
{
	GENERATED_BODY()

public:
	ATransitionSenderActor();

	void SendTransition(TSubclassOf<UUserWidget> loadingScreenWidget = nullptr);

private:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Transition Settings", meta = (AllowPrivateAccess = "true"))
	FString _transitionId;

	UPROPERTY(EditAnywhere, Category = "Transition Settings", meta = (AllowPrivateAccess = "true"))
	FName _targetLevelName;

	UPROPERTY(EditAnywhere, Category = "Transition Settings")
	TSubclassOf<UUserWidget> _loadingScreen;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Transition Settings", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* _triggerComponent;

	FTimerHandle _timerHandle;

	void LoadLevel();

	UFUNCTION()
	void OnObjectOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

};
