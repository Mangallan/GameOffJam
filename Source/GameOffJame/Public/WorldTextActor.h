// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components\TextRenderComponent.h"
#include "WorldTextActor.generated.h"

class UTextRenderComponent;

UCLASS()
class GAMEOFFJAME_API AWorldTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldTextActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WorldText", meta = (AllowPrivateAccess="true"))
	UTextRenderComponent* TextRender;

	int WorldSizeDefault = 24;
	EHorizTextAligment HorizontalAlignmentDefault = EHorizTextAligment::EHTA_Center;

	AActor* Associate;

	FTextFormat DescribedObjectFormat = FTextFormat::FromString("{0}\n{1}\n{2}");


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "WorldText")
	void UpdateText(FText text);

	// Associates an actor for continuous text updates
	UFUNCTION(BlueprintCallable, Category = "WorldText")
	void AssociateDescribedObject(AActor* actor);

	UFUNCTION(BlueprintCallable, Category = "WorldText")
	const AActor* GetAssociate() const;
};
