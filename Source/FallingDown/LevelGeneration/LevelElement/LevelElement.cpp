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
	
}

// Called every frame
void ALevelElement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

