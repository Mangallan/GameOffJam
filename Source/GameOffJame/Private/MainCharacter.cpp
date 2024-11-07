// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"

#include "Interactable.h"
#include "InteractorComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractorComponent = CreateDefaultSubobject<UInteractorComponent>("Interactor");
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::Move_Implementation(FVector2D inputDirection)
{
	UE_LOG(LogTemp, Warning, TEXT("Move"))
	if (Controller)
	{
		FRotator yawRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);
		FRotationMatrix rotMatrix(yawRotation);
		FVector forward(rotMatrix.GetUnitAxis(EAxis::X));
		FVector right(rotMatrix.GetUnitAxis(EAxis::Y));

		AddMovementInput(forward, BaseMoveSpeed * inputDirection.Y);
		AddMovementInput(right, BaseMoveSpeed * inputDirection.X);
	}
}

void AMainCharacter::Look_Implementation(FVector2D inputRotation)
{
	AddControllerYawInput(BaseLookSpeed * inputRotation.X);
	AddControllerPitchInput(-1 * BaseLookSpeed * inputRotation.Y);
}

void AMainCharacter::Interact_Implementation(bool interacting)
{
	if (InteractorComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interacting"))
		InteractorComponent->SetInteract(interacting);
	}
}