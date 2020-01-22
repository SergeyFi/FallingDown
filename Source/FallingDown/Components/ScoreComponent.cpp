// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "ScoreComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

// Sets default values for this component's properties
UScoreComponent::UScoreComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UScoreComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UScoreComponent::CalculateScore(float DeltaTime)
{
	if (Controller != nullptr && Controller->GetPawn() != nullptr)
	{
		if (Controller->GetPawn()->GetLocalRole() == ROLE_Authority)
		{
			Score += Controller->GetPawn()->GetVelocity().Z / -1000.0f * DeltaTime;
		}
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

void UScoreComponent::SetController(class AActor* PlayerController)
{
	Controller = Cast<APlayerController>(PlayerController);
}

