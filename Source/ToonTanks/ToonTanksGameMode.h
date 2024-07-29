// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bPlayerWon);
	
private:
	void HandleStartGame();
	int GetEnemyTurretCount();
	
	float StartDelay = 3.0f;
	int _targetTurrets = 0;
	
	class ATank* _playerTank;
	class AToonTanksPlayerController* _playerController;

	
};
