// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
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

	if (!PlayerTank) { return; }

	// Aim at location of player tank
	auto AimLocation = PlayerTank->GetActorLocation();

	AimLocation.Z += 150.f;

	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->Aim(AimLocation);

	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnPosessedTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }

		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPosessedTankDeath);
	}
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
