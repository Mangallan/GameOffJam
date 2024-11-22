// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSubsystem.h"

#include "Engine/DataTable.h"

void UObjectiveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	LoadObjectives();
}

void UObjectiveSubsystem::Deinitialize()
{

}

void UObjectiveSubsystem::LoadObjectives()
{
	UDataTable* objectiveData = LoadObject<UDataTable>(nullptr, *_ObjectivesPath);

	if (objectiveData)
	{
		objectiveData->ForeachRow<FObjective>(
			"Loading Objective Data",
			[&](FName rowName, FObjective objective) { LoadObjectiveHelper(rowName, objective); });
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load in objectives data from path: %s"), *_ObjectivesPath)
	}
}

void UObjectiveSubsystem::LoadObjectiveHelper(FName rowName, FObjective objective)
{
	Objectives.Add(objective);
}

void UObjectiveSubsystem::CompleteObjective(int ID)
{

	for (int i = 0; i < Objectives.Num(); i++)
	{
		if (Objectives[i].ObjectiveID == ID && !Objectives[i].IsCompleted)
		{
			Objectives[i].IsCompleted = true;

			if (ObjectiveCompletedDelegateBindings.Contains(ID))
			{

				ObjectiveCompletedDelegateBindings[ID].Broadcast(Objectives[i]);
			}
		}
	}
}

void UObjectiveSubsystem::CompleteObjectiveByName(FString objectiveName)
{
	for (int i = 0; i < Objectives.Num(); i++)
	{
		if (Objectives[i].ObjectiveName == objectiveName && !Objectives[i].IsCompleted)
		{
			Objectives[i].IsCompleted = true;

			if (ObjectiveCompletedDelegateBindings.Contains(Objectives[i].ObjectiveID))
			{
				ObjectiveCompletedDelegateBindings[Objectives[i].ObjectiveID].Broadcast(Objectives[i]);
			}
		}
	}
}

void UObjectiveSubsystem::BindFunctionToObjective(int ID, FCompletedObjectiveDelegate delegate)
{
	if (!ObjectiveCompletedDelegateBindings.Contains(ID))
	{
		ObjectiveCompletedDelegateBindings.Add(ID, FCompletedObjectiveEvent());
	}

	ObjectiveCompletedDelegateBindings[ID].Add(delegate);
}

void UObjectiveSubsystem::BindFunctionToObjectiveByName(FString objectiveName, FCompletedObjectiveDelegate delegate)
{
	// This could be cleaned up
	for (int i = 0; i < Objectives.Num(); i++)
	{
		if (Objectives[i].ObjectiveName == objectiveName)
		{
			int id = Objectives[i].ObjectiveID;

			BindFunctionToObjective(id, delegate);
		}
	}
}