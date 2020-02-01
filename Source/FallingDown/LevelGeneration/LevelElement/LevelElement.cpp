// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelElement.h"
#include "Engine/World.h"
#include "Actors/ScoreActor/ScoreActor.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ALevelElement::ALevelElement()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	RootComponent = Mesh;

	ScoreActorSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ScoreActorSpawnPosition"));
	ScoreActorSpawnPosition->SetupAttachment(Mesh);
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
			int32 RandomRotation = FMath::RandRange(0, 360);
			AddActorLocalRotation(FRotator(0.0f, RandomRotation, 0.0f));
		}
	}
}

void ALevelElement::SpawnScoreActor()
{
	int32 Probability = FMath::RandRange(0, 100);

	if (Probability < SpawnProbability)
	{
		if (ScoreActorClass != NULL)
		{
			FTransform SpawnTransform = GetTransform();
			SpawnTransform.SetLocation(ScoreActorSpawnPosition->GetComponentLocation());
			SpawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));

			GetWorld()->SpawnActor<AScoreActor>(ScoreActorClass, SpawnTransform);
		}
	}


}

// Called every frame
void ALevelElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

