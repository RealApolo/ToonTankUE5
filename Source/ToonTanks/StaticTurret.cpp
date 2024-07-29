// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticTurret.h"

#include "Kismet/GameplayStatics.h"
#include "Tank.h"

void AStaticTurret::BeginPlay()
{
	Super::BeginPlay();
	_tankRef = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(_fireRateTimerHandle, this, &AStaticTurret::CheckFireCondition, _fireRate, true);
}

void AStaticTurret::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Warning, TEXT("Turret %s is destroyed!"), *GetName());
	Destroy();
}

void AStaticTurret::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (_tankRef)
	{
		
		FVector PlayerLocation = _tankRef->GetActorLocation();
	
		if (IsTargetOnRange(PlayerLocation))
		{
			PointTurretAt(PlayerLocation);
		}
	}	
}

void AStaticTurret::CheckFireCondition()
{
	if (!_tankRef)
		return;
	
	FVector PlayerLocation = _tankRef->GetActorLocation();;
	if (IsTargetOnRange(PlayerLocation) && IsTargetVisible(PlayerLocation))
		Fire();
}

bool AStaticTurret::IsTargetOnRange(FVector TargetLocation)
{
	return FVector::Dist(TargetLocation, GetActorLocation()) <= _range;
}

bool AStaticTurret::IsTargetVisible(FVector TargetLocation)
{
	FHitResult HitResult;
	FVector StartLocation = GetBulletSpawnLocation();
	FVector EndLocation = StartLocation + GetBulletSpawnForwardDirection() * _range;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	bool isLineHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility, CollisionParams);
	return isLineHit && HitResult.GetActor() == _tankRef;
}
