// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();
	void HandleDestruction();
	
protected:
	void PointTurretAt(FVector Location);
	FVector GetBulletSpawnLocation();
	FVector GetBulletSpawnForwardDirection();
	UFUNCTION(BlueprintCallable, Category= "ShootSystem")
	void Fire();
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Capsule Collider")
	class UCapsuleComponent* _capsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Base Mesh")
	UStaticMeshComponent* _baseMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Turrent Mesh")
	UStaticMeshComponent* _turretMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Components", meta=(AllowPrivateAccess = "true"), DisplayName="Projectile Spawn Point")
	USceneComponent* _projectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "Death", meta=(AllowPrivateAccess = "true"), DisplayName="Death Particle System")
	class UParticleSystem* _deathParticleSystemComponent;
	
	UPROPERTY(EditDefaultsOnly, Category= "ShootSystem", DisplayName="Bullet BP")
	TSubclassOf<class  ABullet> _bulletBP;

	UPROPERTY(EditDefaultsOnly, Category= "Death", DisplayName="Camera Shaker")
	TSubclassOf<class UCameraShakeBase> _deathShake;

	UPROPERTY(EditDefaultsOnly, Category= "Death", DisplayName="Death Sound")
	class USoundBase* _deathSound;
};
