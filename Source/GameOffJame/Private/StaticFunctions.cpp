// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticFunctions.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/KismetInputLibrary.h"


FText UStaticFunctions::GetActionActiveKeyBind(const FName actionName)
{
	FText result;
	TArray<FInputActionKeyMapping> mappings;
	UInputSettings* inputSettings = UInputSettings::GetInputSettings();

	inputSettings->GetActionMappingByName(actionName, mappings);

	if (mappings.Num() > 0)
	{
		FInputActionKeyMapping action = mappings[0];

		bool isGamepadKey = UKismetInputLibrary::Key_IsGamepadKey(action.Key);

	}

	return result;
}