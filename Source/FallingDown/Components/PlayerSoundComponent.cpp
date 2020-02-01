// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "PlayerSoundComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Players/PlayerState/PlayerBaseState.h"
#include "Components/ScoreComponent.h"
#include "Players/PlayerBase/PlayerBase.h"
#include "Components/HealthComponent.h"

// Sets default values for this component's properties
UPlayerSoundComponent::UPlayerSoundComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPlayerSoundComponent::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerBaseState* PlayerState = GetOwner()->GetInstigatorController()->GetPlayerState<APlayerBaseState>();
	if (PlayerState != nullptr)
	{
		PlayerState->GetScoreComponent()->OnScoreAdd.AddDynamic(this, &UPlayerSoundComponent::PlayScoreAdd);
	}

	UHealthComponent* HealthComponent = Cast<APlayerBase>(GetOwner())->GetHealthComponent();
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDamaged.AddDynamic(this, &UPlayerSoundComponent::PlayDamageAdd);
		HealthComponent->OnHeal.AddDynamic(this, &UPlayerSoundComponent::PlayHealSound);
	}
}

void UPlayerSoundComponent::PlayScoreAdd()
{
	if (ScoreAddSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ScoreAddSound, GetComponentLocation());
	}
}

void UPlayerSoundComponent::PlayHealSound()
{
	if (HealSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HealSound, GetComponentLocation());
	}
}

void UPlayerSoundComponent::PlayDamageAdd()
{
	if (DamageSound != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DamageSound, GetComponentLocation());
	}
}


