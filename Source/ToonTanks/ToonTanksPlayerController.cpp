// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksPlayerController.h"

void AToonTanksPlayerController::SetUpEnabledInputState(bool bIsEnabled)
{
	UE_LOG(LogTemp, Warning, TEXT("SetUpEnabledInputState: %d"), bIsEnabled);
	bShowMouseCursor = bIsEnabled;
	if (bIsEnabled)
		GetPawn()->EnableInput(this);
	else
		GetPawn()->DisableInput(this);
}
