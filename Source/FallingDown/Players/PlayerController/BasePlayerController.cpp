// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "BasePlayerController.h"
#include "Players/PlayerBase/PlayerBase.h"
#include "Components/HealthComponent.h"
#include "Blueprint/UserWidget.h"

ABasePlayerController::ABasePlayerController()
{
	bReplicates = true;
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (Role == ROLE_Authority)
	{
		Player = Cast<APlayerBase>(GetPawn());

		if (Player != nullptr)
		{
			Player->GetHealthComponent()->OnHealthEnded.AddDynamic(this, &ABasePlayerController::OnHealthEnded);
		}
	}
}

void ABasePlayerController::OnHealthEnded_Implementation()
{
	if (GameOverUI != NULL)
	{
		GameOverWidget = CreateWidget<UUserWidget>(this, GameOverUI);

		if (GameOverWidget != nullptr)
		{
			GameOverWidget->AddToViewport();
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;

			UE_LOG(LogTemp, Warning, TEXT("Your message"));
		}
	}
}
