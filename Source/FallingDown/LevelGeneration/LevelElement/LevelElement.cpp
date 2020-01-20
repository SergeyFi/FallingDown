// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelElement.h"

// Sets default values
ALevelElement::ALevelElement()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

}

// Called when the game starts or when spawned
void ALevelElement::BeginPlay()
{
	Super::BeginPlay();

	RandomRotation();
	
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

// Called every frame
void ALevelElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

