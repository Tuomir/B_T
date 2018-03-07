// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }
	else 
	{
		return Cast<ATank>(PlayerPawn);
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI controller not found"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s controlled by AI controller"), *GetControlledTank()->GetName())
	}

	if (!GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s not finding player tank"), *GetControlledTank()->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank %s"), *GetPlayerTank()->GetName())
	}
}
