// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Bullet.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = _capsuleComponent;

	_baseMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	_turretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));

	_baseMeshComponent->SetupAttachment(_capsuleComponent);
	_turretMeshComponent->SetupAttachment(_baseMeshComponent);
	
	_projectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	_projectileSpawnPoint->SetupAttachment(_turretMeshComponent);
}

void ABasePawn::HandleDestruction()
{
	if (_deathParticleSystemComponent)
		UGameplayStatics::SpawnEmitterAtLocation(this, _deathParticleSystemComponent, GetActorLocation(), GetActorRotation());
	if (_deathSound)
		UGameplayStatics::PlaySoundAtLocation(this, _deathSound, GetActorLocation());
	if (_deathShake)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(_deathShake);
}

FVector ABasePawn::GetBulletSpawnLocation()
{
	return _projectileSpawnPoint->GetComponentLocation();
}

FVector ABasePawn::GetBulletSpawnForwardDirection()
{
	return _projectileSpawnPoint->GetForwardVector();
}

void ABasePawn::PointTurretAt(FVector Location)
{	
	FVector TurretLocation = RootComponent->GetComponentLocation();
	FRotator ObjectiveRotation = (FVector(Location - TurretLocation)).Rotation();
	ObjectiveRotation.Pitch = 0.0f;
	ObjectiveRotation.Roll = 0.0f;
	FRotator CurrentRotation = _turretMeshComponent->GetComponentRotation();
	FRotator SmoothRotation = FMath::RInterpTo(CurrentRotation, ObjectiveRotation, GetWorld()->DeltaTimeSeconds, 2.0f);
	_turretMeshComponent->SetWorldRotation(SmoothRotation);
}

void ABasePawn::Fire()
{
	auto projectile = GetWorld()->SpawnActor<ABullet>(_bulletBP, GetBulletSpawnLocation(), GetBulletSpawnForwardDirection().Rotation());
	projectile->SetOwner(this);
}