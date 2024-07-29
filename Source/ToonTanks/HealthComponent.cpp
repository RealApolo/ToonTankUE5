// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	_currentHealth = _maxHealth;
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	_gameModeRef = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void UHealthComponent::DamageTaken(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	_currentHealth -= DamageAmount;
	UE_LOG(LogTemp, Warning, TEXT("Actor %s took %f damage from %s! CurrentHP=%f"), *DamagedActor->GetName(), DamageAmount, *DamageCauser->GetName(), _currentHealth);
	if (_currentHealth <= 0.0f)
	{
		_gameModeRef->ActorDied(DamagedActor);
		UE_LOG(LogTemp, Warning, TEXT("Actor %s is dead!"), *DamagedActor->GetName());
	}
}

