// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get player tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// Get controlled AI tank
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		// move towards player tank
		auto Goal = Cast<ATank>(PlayerTank);
		MoveToActor(Goal, AcceptanceRadius);

		// Aim at location of player tank
		auto AimLocation = Cast<ATank>(PlayerTank)->GetActorLocation();
		ControlledTank->AimAt(AimLocation);

		// TODO fire if / when ready
		ControlledTank->Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No player tank found for AI controller!"))
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
