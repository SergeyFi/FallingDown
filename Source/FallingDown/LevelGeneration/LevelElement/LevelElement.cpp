// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "LevelElement.h"

// Sets default values
ALevelElement::ALevelElement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

