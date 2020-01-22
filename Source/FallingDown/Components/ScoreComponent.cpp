// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "ScoreComponent.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPawn = GetOwner();
}


void UScoreComponent::CalculateScore(float DeltaTime)
{
	if (OwningPawn != nullptr && GetOwnerRole() == ROLE_Authority)
	{
		Score += OwningPawn->GetVelocity().Z / 100.0f * DeltaTime;
	}
}

// Called every frame
void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CalculateScore(DeltaTime);
}

void UScoreComponent::AddScore(float ExtraScore)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Score += ExtraScore;
	}
}

