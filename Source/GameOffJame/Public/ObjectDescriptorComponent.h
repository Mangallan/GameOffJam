// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectDescriptorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFFJAME_API UObjectDescriptorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectDescriptorComponent();

protected:

	UPROPERTY(EditAnywhere, Category = "Description", meta = (AllowPrivateAccess="true"))
	FName DisplayName;

	UPROPERTY(EditAnywhere, Category = "Description", meta = (AllowPrivateAccess = "true"))
	FText Description;

	UPROPERTY(EditAnywhere, Category = "Description", meta = (AllowPrivateAccess = "true"))
	FText ActionDescription;

public:

	UFUNCTION(BlueprintCallable, Category = "Description")
	FName GetDisplayName() { return DisplayName; }

	UFUNCTION(BlueprintCallable, Category = "Description")
	FText GetDescription() { return Description; }

	UFUNCTION(BlueprintCallable, Category = "Description")
	FText GetActionDescription() { return ActionDescription; }
		
};
