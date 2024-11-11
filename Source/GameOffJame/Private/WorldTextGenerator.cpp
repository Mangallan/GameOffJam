// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTextGenerator.h"

#include "Components\ShapeComponent.h"
#include "Components\TextRenderComponent.h"
#include "DescribedObject.h"
#include "WorldTextActor.h"

// Sets default values for this component's properties
UWorldTextGenerator::UWorldTextGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWorldTextGenerator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWorldTextGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWorldTextGenerator::RegisterTextRenderRangeVolume(UShapeComponent* detectionVolume)
{
	detectionVolume->OnComponentBeginOverlap.AddDynamic(this, &UWorldTextGenerator::OnOverlap);
	detectionVolume->OnComponentEndOverlap.AddDynamic(this, &UWorldTextGenerator::OnOverlapEnd);
}

void UWorldTextGenerator::OnOverlap(
	UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex,
	bool bFromSweep,
	const FHitResult& sweepResult)
{
	if (otherActor->Implements<UDescribedObject>())
	{
		GenerateActorAssociatedWorldText(otherActor);
	}
}

void UWorldTextGenerator::OnOverlapEnd(
	UPrimitiveComponent* overlappedComponent,
	AActor* otherActor,
	UPrimitiveComponent* otherComp,
	int32 otherBodyIndex)
{
	if (otherActor->Implements<UDescribedObject>())
	{
		int32 toDeleteIndex = -1;

		for (int i = 0; i < TrackedWorldTextActors.Num(); i++)
		{
			if (TrackedWorldTextActors[i]->GetAssociate() == otherActor)
			{
				toDeleteIndex = i;
				break;
			}
		}

		if (toDeleteIndex >= 0)
		{
			AActor* toDelete = TrackedWorldTextActors[toDeleteIndex];

			TrackedWorldTextActors.RemoveAt(toDeleteIndex);
			toDelete->Destroy();

		}
	}
}

void UWorldTextGenerator::GenerateActorAssociatedWorldText(AActor* associate)
{
	UWorld* world = GetWorld();
	FVector spawnLocation = associate->GetActorLocation();

	AWorldTextActor* textActor = world->SpawnActor<AWorldTextActor>(AWorldTextActor::StaticClass(), FTransform(spawnLocation));

	textActor->AssociateDescribedObject(associate);

	TrackedWorldTextActors.Add(textActor);
}