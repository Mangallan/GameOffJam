// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueConsumer.generated.h"

class UDialogueProducer;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFFJAME_API UDialogueConsumer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueConsumer();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueStarted, UDialogueProducer*, dialogueProducer);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueConsumed, FText, dialogue);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDialogueEnded);

	UPROPERTY(BlueprintAssignable, Category = Dialogue)
	FDialogueStarted DialogueStartedEvent;

	UPROPERTY(BlueprintAssignable, Category = Dialogue)
	FDialogueConsumed DialogueConsumedEvent;
	
	UPROPERTY(BlueprintAssignable, Category = Dialogue)
	FDialogueEnded DialogueEndedEvent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UDialogueProducer* DialogueProducer;

public:	

	UFUNCTION(BlueprintCallable, Category = DialogueConsumer)
	void StartDialogue(UDialogueProducer* producer);

	UFUNCTION(BlueprintCallable, Category = DialogueConsumer)
	bool ConsumeDialogue();

	UFUNCTION(BlueprintCallable, Category = DialogueConsumer)
	void EndDialogue();

	UFUNCTION(BlueprintCallable, Category = DialogueConsumer)
	bool HasActiveDialogue();
};
