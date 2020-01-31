// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PlayerSoundComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UPlayerSoundComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerSoundComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	class USoundBase* ScoreAddSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	class USoundBase* DamageSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sounds")
	class USoundBase* HealSound;

	UFUNCTION()
	void PlayScoreAdd();

	UFUNCTION()
	void PlayHealSound();

	UFUNCTION()
	void PlayDamageAdd();

};
