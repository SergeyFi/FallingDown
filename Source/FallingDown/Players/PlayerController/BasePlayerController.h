// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"


UCLASS()
class FALLINGDOWN_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ABasePlayerController();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class APlayerBase* Player;

	class UUserWidget* GameOverWidget;

	UFUNCTION(Client, Reliable)
	void OnHealthEnded();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> GameOverUI;

};
