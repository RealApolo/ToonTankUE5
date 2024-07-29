// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "StaticTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"

class AStaticTurret;

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleStartGame();
}

void AToonTanksGameMode::HandleStartGame()
{
	_playerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	_playerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));
	_targetTurrets = GetEnemyTurretCount();
	StartGame();
	if (_playerController)
	{
		_playerController->SetUpEnabledInputState(false);
		FTimerHandle StartGameTimerHandle;
		FTimerDelegate StartGameTimerDelegate = FTimerDelegate::CreateUObject(_playerController, &AToonTanksPlayerController::SetUpEnabledInputState, true);
		GetWorldTimerManager().SetTimer(StartGameTimerHandle, StartGameTimerDelegate, StartDelay, false);
	}
}

int AToonTanksGameMode::GetEnemyTurretCount()
{
	TArray<AActor*> _turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStaticTurret::StaticClass(), _turrets);
	return _turrets.Num();
}

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == _playerTank)
	{
		_playerTank->HandleDestruction();
		if (_playerController)
		{
			_playerController->SetUpEnabledInputState(false);
			GameOver(false);
		}
	}	
	else if (AStaticTurret* DestroyedTurret = Cast<AStaticTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		_targetTurrets--;
		if (_targetTurrets <= 0)
		{
			GameOver(true);
		}
	}
}
