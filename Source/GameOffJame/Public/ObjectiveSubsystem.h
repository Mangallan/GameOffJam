// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/DelegateSignatureImpl.inl"

#include "ObjectiveSubsystem.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct FObjective : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
	int ObjectiveID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
	FString ObjectiveName;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Objectives)
	//TMap<FString, float> CompletionRequirements;

	bool IsCompleted = false;
};

/**
 * 
 */
UCLASS()
class GAMEOFFJAME_API UObjectiveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE_OneParam(FCompletedObjectiveDelegate, FObjective, completedObjective);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompletedObjectiveEvent, FObjective, completedObjective);

protected:
	UPROPERTY()
	TArray<FObjective> Objectives;

	void LoadObjectives();
	void LoadObjectiveHelper(FName rowName, FObjective objective);

	UPROPERTY()
	TMap<int, FCompletedObjectiveEvent> ObjectiveCompletedDelegateBindings;
	
	//TODO bad, don't hardcode paths
	FString _ObjectivesPath = "/Game/Data/ObjectivesDataTable.ObjectivesDataTable";

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void CompleteObjective(int ID);

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void CompleteObjectiveByName(FString objectiveName);

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void BindFunctionToObjective(int ID, FCompletedObjectiveDelegate delegate);

	UFUNCTION(BlueprintCallable, Category = Objectives)
	void BindFunctionToObjectiveByName(FString objectiveName, FCompletedObjectiveDelegate delegate);
};