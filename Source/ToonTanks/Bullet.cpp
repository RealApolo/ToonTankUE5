// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	_projectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = _projectileMeshComponent;

	_projectileMoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Mover"));
	_projectileMoveComponent->InitialSpeed = 2000.0f;
	_projectileMoveComponent->MaxSpeed = 2000.0f;

	_TrailParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle System"));
	_TrailParticleSystemComponent->SetupAttachment(_projectileMeshComponent);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	_projectileMeshComponent->OnComponentHit.AddDynamic(this, &ABullet::OnHit);
	if (_spawnSound)
		UGameplayStatics::PlaySoundAtLocation(this, _spawnSound, GetActorLocation());
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	auto owner = GetOwner();
	if (!owner)
	{
		Destroy();
		return;
	}

	auto instigator = owner->GetInstigatorController();
	if (!instigator || !OtherActor || OtherActor == instigator)
	{
		Destroy();
		return;
	}
	
	UGameplayStatics::ApplyDamage(OtherActor, 15.0f, instigator, GetOwner(), nullptr);
	if (_hitParticle)
		UGameplayStatics::SpawnEmitterAtLocation(this, _hitParticle, GetActorLocation(), GetActorRotation());
	if (_hitSound)
		UGameplayStatics::PlaySoundAtLocation(this, _hitSound, GetActorLocation());
	Destroy();
}

