// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputController.generated.h"
	
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API AInputController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

	void SetupInputs();

	void SendMoveInput(const FInputActionValue& Value);
	void SendLookInput(const FInputActionValue& Value);
	void SendRiseInput(const FInputActionValue& Value);
	void SendFallInput(const FInputActionValue& Value);
	void SendInteractInput(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess="true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveInput;

	// Disabled for fixed camera. Can change later
	//UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	//UInputAction* LookInput;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RiseInput;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FallInput;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractInput;
	
public:

};
