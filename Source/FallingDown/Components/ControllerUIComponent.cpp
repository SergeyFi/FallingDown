// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "ControllerUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UControllerUIComponent::UControllerUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UControllerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	if (HealthWidgetClass != NULL)
	{
		HealthWidget = CreateWidget(Cast<APlayerController>(GetOwner()), HealthWidgetClass);
		
		if (HealthWidget != nullptr)
		{
			HealthWidget->AddToViewport();
		}
	}

	if (ScoreWidgetClass != NULL)
	{
		ScoreWidget = CreateWidget(Cast<APlayerController>(GetOwner()), ScoreWidgetClass);

		if (ScoreWidget != nullptr)
		{
			ScoreWidget->AddToViewport();
		}
	}
}

