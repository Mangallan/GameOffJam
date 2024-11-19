// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueConsumer.h"

#include "DialogueProducer.h"

// Sets default values for this component's properties
UDialogueConsumer::UDialogueConsumer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogueConsumer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UDialogueConsumer::StartDialogue(UDialogueProducer* producer)
{
	DialogueProducer = producer;
	DialogueStartedEvent.Broadcast(producer);
	ConsumeDialogue();
}

bool UDialogueConsumer::ConsumeDialogue()
{
	bool consumed = false;

	if (DialogueProducer)
	{
		FText dialogue = DialogueProducer->GetNextLine();

		if (dialogue.IsEmpty())
		{
			EndDialogue();
		}
		else
		{
			consumed = true;
			DialogueConsumedEvent.Broadcast(dialogue);
		}
	}

	return consumed;
}

void UDialogueConsumer::EndDialogue()
{
	DialogueProducer = nullptr;
	DialogueEndedEvent.Broadcast();
}

bool UDialogueConsumer::HasActiveDialogue()
{
	return DialogueProducer != nullptr;
}