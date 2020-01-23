// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Health = 5;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHealthComponent::AddHealth(int32 Heal)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Health += Heal;

		OnHeal.Broadcast();
	}
}

void UHealthComponent::RemoveHealth(int32 Damage)
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		Health -= Damage;

		OnDamaged.Broadcast();

		if (Health <= 0)
		{
			OnHealthEnded.Broadcast();

			Health = 0;
		}
	}
}

