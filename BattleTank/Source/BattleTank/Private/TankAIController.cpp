// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get player tank
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	// Get controlled AI tank
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank || ControlledTank)) { return; }

	// move towards player tank
	auto Goal = PlayerTank;
	MoveToActor(Goal, AcceptanceRadius);

	// Aim at location of player tank
	auto AimLocation = PlayerTank->GetActorLocation();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->Aim(AimLocation);

	// TODO fire if / when ready
	AimingComponent->Fire();
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
