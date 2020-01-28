// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelElement.generated.h"

UCLASS()
class FALLINGDOWN_API ALevelElement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelElement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	bool bIsRandomRotated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Score")
	int32 SpawnProbability;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Score")
	TSubclassOf<class AScoreActor> ScoreActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties|Score", meta = (MakeEditWidget = true))
	FVector ScoreActorPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RandomRotation();

	void SpawnScoreActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
