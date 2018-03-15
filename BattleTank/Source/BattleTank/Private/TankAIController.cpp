// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		// TODO move towards player tank

		// Get player tank
		auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		// Aim at location of player tank
		auto AimLocation = Cast<ATank>(PlayerPawn)->GetActorLocation();
		Cast<ATank>(GetPawn())->AimAt(AimLocation);

		// TODO fire if / when ready
		Cast<ATank>(GetPawn())->Fire();
	}
}

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
}
