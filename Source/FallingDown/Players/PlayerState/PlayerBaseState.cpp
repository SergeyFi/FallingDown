// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "PlayerBaseState.h"
#include "Components/ScoreComponent.h"
#include "GameFramework/PlayerController.h"

APlayerBaseState::APlayerBaseState()
{
	ScoreComponent = CreateDefaultSubobject<UScoreComponent>(TEXT("ScoreComponent"));
	
}

void APlayerBaseState::BeginPlay()
{
	Super::BeginPlay();
}

UScoreComponent* APlayerBaseState::GetScoreComponent()
{
	return ScoreComponent;
}
