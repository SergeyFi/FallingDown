// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "LevelGenerator.generated.h"

USTRUCT()
struct FLevelStage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float StageDurationInMinutes;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class ALevelElement>> StageElements;
};

UCLASS()
class FALLINGDOWN_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	int32 CurrentStageIndex;

	UPROPERTY(VisibleAnywhere, Category = "Properties")
	float StageDuration;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float ElementGenerationRate;

	UPROPERTY(EditAnywhere, Category = "Properties")
	int32 ElementMaxCount;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float LowestPointShift;

	UPROPERTY(EditAnywhere, Category = "Properties")
	float HighestPointShift;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TArray<FLevelStage> LevelStages;

	FVector CurrentSpawnLocation;

	TArray<class ALevelElement*> SpawnedElements;

	FTimerHandle StageGenerationTimer;

	void StartStageGeneration();

	void StageGeneration();

	void ManageStages();

	void SpawnElement(int32 ElementIndex);

	int32 GenerateRandomElementIndex();

	void AddLevelElementToElementsArray(ALevelElement* LevelElement);

	void ManageElementsArray();

	float FindExtremePlayerLocation(bool Lowest);
};
