// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelGenerator.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "LevelGeneration/LevelElement/LevelElement.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	StartStageGeneration();
	
}

void ALevelGenerator::StartStageGeneration()
{
	if (LevelStages.Num() != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(StageGenerationTimer, this, 
			&ALevelGenerator::StageGeneration, ElementGenerationRate, true);
	}
}

void ALevelGenerator::StageGeneration()
{
	StageDuration += ElementGenerationRate;
	ManageStages();
}

void ALevelGenerator::ManageStages()
{
	if (StageDuration >= LevelStages[CurrentStageIndex].StageDurationInMinutes * 60.0f)
	{
		if (CurrentStageIndex < LevelStages.Num())
		{
			CurrentStageIndex += 1;
			StageDuration = 0.0f;
		}
		else
		{
			CurrentStageIndex = 0;
		}
	}
}

void ALevelGenerator::SpawnElement(int32 ElementIndex)
{
	TSubclassOf<ALevelElement> ElementToSpawn = LevelStages[CurrentStageIndex].StageElements[ElementIndex];

	static FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	ALevelElement* LevelElement = GetWorld()->SpawnActor<ALevelElement>(ElementToSpawn, SpawnLocation, SpawnRotation);

	// Set new SpawnLocation
	FVector Origin;
	FVector BoxExtent;

	LevelElement->GetActorBounds(true, Origin, BoxExtent);

	SpawnLocation += FVector(0.0f, 0.0f, BoxExtent.Z);
}
