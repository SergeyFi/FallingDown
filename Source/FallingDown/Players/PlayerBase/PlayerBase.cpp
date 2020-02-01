// Copyright 2020 Sergey Firsov. All Rights Reserved.


#include "PlayerBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/HealthComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "LevelGeneration/LevelElement/LevelElement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PlayerSoundComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleRadius = 60.0f;

	GetCharacterMovement()->AirControl = 1.0f;
	GetCharacterMovement()->MaxWalkSpeed = 2000.0f;


	GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleRadius);
	GetCapsuleComponent()->SetCapsuleRadius(CapsuleRadius);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	SpringArm->SetupAttachment(Cast<USceneComponent>(GetCapsuleComponent()));

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnHealthEnded.AddDynamic(this, &APlayerBase::OnHealthEnded);

	SoundComponent = CreateDefaultSubobject<UPlayerSoundComponent>(TEXT("SoundComponent"));
	SoundComponent->SetupAttachment(Camera);

	GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &APlayerBase::OnMeshOverlap);
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerBase::OnMeshOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALevelElement* LevelElement = Cast<ALevelElement>(OtherActor);

	if (LevelElement != nullptr)
	{
		HealthComponent->RemoveHealth(1);
	}
}

void APlayerBase::OnHealthEnded()
{
	Destroy();
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerBase::MoveRight);

}

void APlayerBase::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerBase::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

UHealthComponent* APlayerBase::GetHealthComponent()
{
	return HealthComponent;
}

