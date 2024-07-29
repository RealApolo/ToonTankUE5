// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void DamageTaken( AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	UPROPERTY(EditDefaultsOnly,  BlueprintReadOnly, Category= "Health", meta=(AllowPrivateAccess = "true"), DisplayName="Max Health")
	float _maxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,  Category= "Health", meta=(AllowPrivateAccess = "true"), DisplayName="Current Health")
	float _currentHealth;

	class AToonTanksGameMode* _gameModeRef;		
};
