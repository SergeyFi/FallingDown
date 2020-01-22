// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlayerBaseState.generated.h"


UCLASS()
class FALLINGDOWN_API APlayerBaseState : public APlayerState
{
	GENERATED_BODY()

public:

	APlayerBaseState();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UScoreComponent* ScoreComponent;
	
};
