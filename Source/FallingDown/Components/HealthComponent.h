// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	class USphereComponent* SphereComponent;

public:

	void AddHealth(int32 Heal);

	void RemoveHealth(int32 Damage);

	FHealthDelegate OnHealthEnded;

	FHealthDelegate OnDamaged;

	FHealthDelegate OnHeal;

};
