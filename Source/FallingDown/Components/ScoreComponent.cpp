// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "ScoreComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UScoreComponent::AddScore(float ExtraScore)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Score += ExtraScore;
	}
}
