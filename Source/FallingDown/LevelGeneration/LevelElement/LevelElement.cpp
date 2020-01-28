// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelElement.h"
#include "Engine/World.h"
#include "Actors/ScoreActor/ScoreActor.h"

// Sets default values
ALevelElement::ALevelElement()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

}

// Called when the game starts or when spawned
void ALevelElement::BeginPlay()
{
	Super::BeginPlay();

	RandomRotation();

	SpawnScoreActor();
	
}

void ALevelElement::RandomRotation()
{
	if (Role == ROLE_Authority)
	{
		if (bIsRandomRotated)
		{
			int32 RandomRotation = 90.0f * FMath::RandRange(0, 3);
			AddActorLocalRotation(FRotator(0.0f, RandomRotation, 0.0f));
		}
	}
}

void ALevelElement::SpawnScoreActor()
{
	if (ScoreActorClass != NULL)
	{
		FTransform SpawnTransform = GetTransform();
		SpawnTransform.SetLocation(ScoreActorPosition);
		SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

		GetWorld()->SpawnActor<AScoreActor>(ScoreActorClass, SpawnTransform);
	}
}

// Called every frame
void ALevelElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

