// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOONTANKS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Projectile Mesh")
	UStaticMeshComponent* _projectileMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Projectile Mover")
	class UProjectileMovementComponent* _projectileMoveComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Projectile Mover")
	class UParticleSystemComponent* _TrailParticleSystemComponent;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	class UParticleSystem* _hitParticle;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	class USoundBase* _hitSound;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	class USoundBase* _spawnSound;
};
