// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelGenerator.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "LevelGeneration/LevelElement/LevelElement.h"
#include "Players/PlayerBase/PlayerBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		CurrentSpawnLocation = GetActorLocation();

		StartStageGeneration();
	}
	
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
	if (Role == ROLE_Authority)
	{
		StageDuration += ElementGenerationRate;
		ManageStages();

		SpawnElement(GenerateRandomElementIndex());

		ManageElementsArray();
	}
}

void ALevelGenerator::ManageStages()
{
	if (StageDuration >= LevelStages[CurrentStageIndex].StageDurationInMinutes * 60.0f)
	{
		if (CurrentStageIndex < LevelStages.Num() - 1)
		{
			CurrentStageIndex += 1;
			StageDuration = 0.0f;
		}
		else
		{
			CurrentStageIndex = 0;
			StageDuration = 0.0f;
		}
	}
}

void ALevelGenerator::SpawnElement(int32 ElementIndex)
{
	if (LevelStages[CurrentStageIndex].StageElements.IsValidIndex(ElementIndex))
	{
		TSubclassOf<ALevelElement> ElementToSpawn = LevelStages[CurrentStageIndex].StageElements[ElementIndex];

		FRotator SpawnRotation = GetActorRotation();

		ALevelElement* LevelElement = GetWorld()->SpawnActor<ALevelElement>(ElementToSpawn, CurrentSpawnLocation, SpawnRotation);

		// Set new SpawnLocation
		FVector Origin;
		FVector BoxExtent;

		LevelElement->GetActorBounds(true, Origin, BoxExtent);

		CurrentSpawnLocation -= FVector(0.0f, 0.0f, BoxExtent.Z * 2);

		SpawnedElements.Add(LevelElement);
	}
}

int32 ALevelGenerator::GenerateRandomElementIndex()
{
	int32 RandomElementIndex = FMath::RandRange(0, LevelStages[CurrentStageIndex].StageElements.Num() - 1);

	return RandomElementIndex;
}

void ALevelGenerator::ManageElementsArray()
{
	ALevelElement* TailElement = SpawnedElements[0];

	if (TailElement != nullptr)
	{
		if (FindExtremePlayerLocation(false) + HighestPointShift < TailElement->GetActorLocation().Z)
		{
			SpawnedElements.RemoveAt(0);

			TailElement->Destroy();
		}
	}
}

float ALevelGenerator::FindExtremePlayerLocation(bool Lowest)
{
	static TArray<AActor*> PlayerActors;

	float LowestPlayerLocation = 0.0f;

	float HighestPlayerLocation = 0.0f;

	if (PlayerActors.Num() == 0)
	{
		UGameplayStatics::GetAllActorsOfClass(this, APlayerBase::StaticClass(), PlayerActors);
	}

	for (AActor* Player : PlayerActors)
	{
		if (Player != nullptr)
		{
			if (LowestPlayerLocation > Player->GetActorLocation().Z)
			{
				LowestPlayerLocation = Player->GetActorLocation().Z;
				HighestPlayerLocation = Player->GetActorLocation().Z;
			}

			if (Player->GetActorLocation().Z > HighestPlayerLocation)
			{
				HighestPlayerLocation = Player->GetActorLocation().Z;
			}
		}
	}

	if (Lowest)
	{
		return LowestPlayerLocation;
	}
	else
	{
		return HighestPlayerLocation;
	}
}
