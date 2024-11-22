// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueProducer.generated.h"

USTRUCT(Blueprintable)
struct FDialogueInstanceInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString DialogueKey;

	UPROPERTY(BlueprintReadOnly)
	bool HasBeenRead;

	UPROPERTY(BlueprintReadOnly)
	int LineCount;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEOFFJAME_API UDialogueProducer : public UActorComponent
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_RetVal(FString, FGetNextDialogueTreeSignature);

public:	
	// Sets default values for this component's properties
	UDialogueProducer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FString ActiveDialogue = "";
	int CurrentDialogueIndex = -1;

	TMap<FString, FDialogueInstanceInfo> DialogueInfos;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess="true"))
	UStringTable* DialogueData;

	FGetNextDialogueTreeSignature GetNextDialogueTreeDelegate;

public:	

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void InitiateDialogue(AActor* initiator);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	FText GetNextLine();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void BindGetNextDialogueTreeFunction(FGetNextDialogueTreeSignature function);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	static FString StripIndexFromDialogueKey(FString key);
};