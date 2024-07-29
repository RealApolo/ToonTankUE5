// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATank::ATank()
{
	_springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	_springArmComponent->SetupAttachment(RootComponent);

	_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_cameraComponent->SetupAttachment(_springArmComponent);
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	_playerController = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (_playerController)
	{
		FHitResult HitResult;
		if (_playerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
			PointTurretAt(HitResult.ImpactPoint);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::MoveVertical(float value)
{
	FVector MovementVector = FVector::ZeroVector;
	MovementVector.X = value * _moveSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalOffset(MovementVector, true);
}

void ATank::Rotate(float value)
{
	FRotator RotationVector = FRotator::ZeroRotator;
	RotationVector.Yaw = value * _rotateSpeed * GetWorld()->DeltaTimeSeconds;
	AddActorLocalRotation(RotationVector, true);
}
