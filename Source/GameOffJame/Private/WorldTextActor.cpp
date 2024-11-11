// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldTextActor.h"

#include "Components\TextRenderComponent.h"
#include "DescribedObject.h"
#include "Kismet/GameplayStatics.h"
#include "Camera\CameraComponent.h"

// Sets default values
AWorldTextActor::AWorldTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Renderer"));
	RootComponent = TextRender;

	TextRender->SetWorldSize(WorldSizeDefault);
	TextRender->SetHorizontalAlignment(HorizontalAlignmentDefault);
}

// Called when the game starts or when spawned
void AWorldTextActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWorldTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update rotation to make sure player can see text properly
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	APawn* controlled = playerController->GetPawn();
	UCameraComponent* camera = controlled->GetComponentByClass<UCameraComponent>();

	if (camera)
	{
		FRotator reverseRotation = -1 * camera->GetComponentRotation();
		reverseRotation.Yaw -= 180;
		SetActorRotation(reverseRotation);
	}

	if (Associate)
	{
		FText actorName = IDescribedObject::Execute_GetDisplayName(Associate);
		FText actorActionPrompt = IDescribedObject::Execute_GetActionDescription(Associate);
		FText actorDescription = IDescribedObject::Execute_GetDescription(Associate);

		FText resultText = FText::FormatOrdered(DescribedObjectFormat, actorName, actorDescription, actorActionPrompt);
		UpdateText(resultText);
	}
}

void AWorldTextActor::UpdateText(FText text)
{
	TextRender->SetText(text);
}

void AWorldTextActor::AssociateDescribedObject(AActor* actor)
{
	if (actor && actor->Implements<UDescribedObject>())
	{
		Associate = actor;
	}
}

const AActor* AWorldTextActor::GetAssociate() const
{
	return Associate;
}