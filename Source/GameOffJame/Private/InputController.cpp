// Fill out your copyright notice in the Description page of Project Settings.


#include "InputController.h"

#include "Controllable.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

void AInputController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* enhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (enhancedInputSubsystem)
	{
		enhancedInputSubsystem->AddMappingContext(DefaultMappingContext, 0);
		SetupInputs();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Input Subsystem!"))
	}
}

void AInputController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	TrackedPawn = pawn;
}

void AInputController::SetupInputs()
{
	UEnhancedInputComponent* inputComponent = Cast<UEnhancedInputComponent>(InputComponent);


	if (inputComponent)
	{
		inputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &AInputController::SendMoveInput);
		//inputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &AInputController::SendLookInput);
		inputComponent->BindAction(RiseInput, ETriggerEvent::Triggered, this, &AInputController::SendRiseInput);
		inputComponent->BindAction(FallInput, ETriggerEvent::Triggered, this, &AInputController::SendFallInput);
		inputComponent->BindAction(InteractInput, ETriggerEvent::Triggered, this, &AInputController::SendInteractInput);
		inputComponent->BindAction(AnyInput, ETriggerEvent::Triggered, this, &AInputController::UpdateLastDeviceUsed);
		inputComponent->BindAction(InventoryInput, ETriggerEvent::Triggered, this, &AInputController::SendInventoryInput);
	}
}

// There's gotta be a better way than repeating function defs
void AInputController::SendMoveInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>()) //Uh, should this be U or I?
	{
		IControllable::Execute_Move(TrackedPawn, Value.Get<FVector2D>());
	}
}

void  AInputController::SendLookInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>())
	{
		IControllable::Execute_Look(TrackedPawn, Value.Get<FVector2D>());
	}
}

void AInputController::SendRiseInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>())
	{
		IControllable::Execute_Rise(TrackedPawn, Value.Get<bool>());
	}
}

void AInputController::SendFallInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>())
	{
		IControllable::Execute_Fall(TrackedPawn, Value.Get<bool>());
	}
}

void AInputController::SendInteractInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>())
	{
		IControllable::Execute_Interact(TrackedPawn, Value.Get<bool>());
	}
}

void AInputController::UpdateLastDeviceUsed(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Any pressed"))
}

void AInputController::SendInventoryInput(const FInputActionValue& Value)
{
	if (TrackedPawn && TrackedPawn->Implements<UControllable>())
	{
		IControllable::Execute_ToggleInventory(TrackedPawn, Value.Get<bool>());
	}
}
