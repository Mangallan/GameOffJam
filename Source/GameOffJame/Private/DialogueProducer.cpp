// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueProducer.h"

#include "DialogueConsumer.h"
#include "Internationalization/StringTable.h"
#include "Kismet/KismetStringTableLibrary.h"

// Sets default values for this component's properties
UDialogueProducer::UDialogueProducer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogueProducer::BeginPlay()
{
	Super::BeginPlay();

	if (DialogueData)
	{
		// Populate dialogue array with all the info needed on the main tree
		TArray<FString> keys = UKismetStringTableLibrary::GetKeysFromStringTable(DialogueData->GetStringTableId());

		for (int i = 0; i < keys.Num(); i++)
		{
			FString uniqueKey = StripIndexFromDialogueKey(keys[i]);

			if (!DialogueInfos.Contains(uniqueKey))
			{
				FDialogueInstanceInfo dialogueInfo = FDialogueInstanceInfo();
				dialogueInfo.DialogueKey = uniqueKey;
				dialogueInfo.HasBeenRead = false;

				DialogueInfos.Add(uniqueKey, dialogueInfo);
			}

			DialogueInfos[uniqueKey].LineCount++;
		}
	}

}

void UDialogueProducer::InitiateDialogue(AActor* initiator)
{
	UDialogueConsumer* dialogueConsumer = initiator->FindComponentByClass<UDialogueConsumer>();

	if (dialogueConsumer && GetNextDialogueTreeDelegate.IsBound())
	{
		CurrentDialogueIndex = 0;
		ActiveDialogue = GetNextDialogueTreeDelegate.Execute();
		dialogueConsumer->StartDialogue(this);
	}
}

FText UDialogueProducer::GetNextLine()
{
	FText result = FText();

	if (!ActiveDialogue.IsEmpty() &&
		DialogueInfos.Contains(ActiveDialogue) &&
		CurrentDialogueIndex >= 0 &&
		CurrentDialogueIndex < DialogueInfos[ActiveDialogue].LineCount)
	{
		// Get the dialogue
		FString key = ActiveDialogue + "_" + FString::FromInt(CurrentDialogueIndex); // not how I want to do it but format functions are making things harder for no apparent reason.
		result = FText::FromStringTable(DialogueData->GetStringTableId(), key);

		// Record keeping on traversed dialogue
		CurrentDialogueIndex++;

		if (CurrentDialogueIndex == DialogueInfos[ActiveDialogue].LineCount)
		{
			DialogueInfos[ActiveDialogue].HasBeenRead = true;
		}
	}

	return result;
}

void UDialogueProducer::BindGetNextDialogueTreeFunction(FGetNextDialogueTreeSignature function)
{
	GetNextDialogueTreeDelegate = function;
}

FString UDialogueProducer::StripIndexFromDialogueKey(FString key)
{
	int lastCharIdx = key.Len();

	key.FindLastChar('_', lastCharIdx);

	FString uniqueKey = key.Left(lastCharIdx);

	return uniqueKey;
}