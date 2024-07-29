// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "StaticTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AStaticTurret : public ABasePawn
{
	GENERATED_BODY()

public:
	void HandleDestruction();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:
	bool IsTargetOnRange(FVector TargetLocation);
	bool IsTargetVisible(FVector TargetLocation);
	void CheckFireCondition();
	
private:

	FTimerHandle _fireRateTimerHandle;
	
	UPROPERTY(VisibleAnywhere, Category= "ShootSystem", DisplayName="Tank Ref")
	class ATank* _tankRef;

	UPROPERTY(EditDefaultsOnly, Category= "ShootSystem", DisplayName="Range")
	float _range = 100.f;

	UPROPERTY(EditDefaultsOnly, Category= "ShootSystem", DisplayName="Fire Rate")
	float _fireRate = 2.0f;
};
