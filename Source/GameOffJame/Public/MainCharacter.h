// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Controllable.h"
#include "MainCharacter.generated.h"

class UInteractorComponent;
class UCameraComponent;
class UDialogueConsumer;

UCLASS()
class GAMEOFFJAME_API AMainCharacter : public ACharacter, public IControllable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (AllowPrivateAccess="true"))
	float BaseMoveSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float BaseLookSpeed = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess="true"))
	UInteractorComponent* InteractorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialogue", meta = (AllowPrivateAccess = "true"))
	UDialogueConsumer* DialogueConsumerComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Overriden functions from Controllable Interface
	void Move_Implementation(FVector2D inputDirection) override;

	void Look_Implementation(FVector2D inputRotation) override;

	void Interact_Implementation(bool interacting) override;
};
