// Copyright 2020 Sergey Firsov. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ControllerUIComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FALLINGDOWN_API UControllerUIComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UControllerUIComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UUserWidget* HealthWidget;

	class UUserWidget* ScoreWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> HealthWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<class UUserWidget> ScoreWidgetClass;
};
