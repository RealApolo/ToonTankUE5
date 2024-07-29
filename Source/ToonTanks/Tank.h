// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	APlayerController* GetPlayerController() const { return _playerController;}
	
protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	
private:
	UFUNCTION(BlueprintCallable, Category= "Movement")
	void MoveVertical(float value);

	UFUNCTION(BlueprintCallable, Category= "Movement")
	void Rotate(float value);
	
private:
	APlayerController* _playerController;
	
	UPROPERTY(VisibleAnywhere, Category= "Components", DisplayName="Spring Arm")
	class USpringArmComponent* _springArmComponent;
	
	UPROPERTY(VisibleAnywhere, Category= "Components", DisplayName="Camera")
	class UCameraComponent* _cameraComponent;

	UPROPERTY(EditAnywhere, Category= "Movement", DisplayName="Move Speed")
	float _moveSpeed = 1.0f;

	UPROPERTY(EditAnywhere, Category= "Movement", DisplayName="Rotate Speed")
	float _rotateSpeed = 1.0f;
};
