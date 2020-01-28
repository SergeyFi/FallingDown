// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "ScoreActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerState.h"
#include "Players/PlayerState/PlayerBaseState.h"
#include "Components/ScoreComponent.h"

// Sets default values
AScoreActor::AScoreActor()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AScoreActor::OnSphereOverlapBegin);

}

// Called when the game starts or when spawned
void AScoreActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreActor::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);

	if (PlayerPawn != nullptr)
	{
		APlayerBaseState* PlayerState = Cast<APlayerBaseState>(PlayerPawn->GetPlayerState());

		if (PlayerState != nullptr)
		{
			PlayerState->GetScoreComponent()->AddScore(Score);
		}
	}
}
