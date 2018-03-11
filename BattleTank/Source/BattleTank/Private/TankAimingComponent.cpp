// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	// Work out difference betwwen current turret rotation and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto DeltaTurretRotator = AimAsRotator - TurretRotator;

	// Rotate turret
	Turret->Rotate(DeltaTurretRotator.Yaw);

	// Elevate barrel
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingComponent::Aim(FVector AimLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		auto Time = GetWorld()->GetTimeSeconds();
		auto OwningTank = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%f: %s: aim solution found"), Time, *OwningTank)
		MoveBarrelTowards(AimLocation);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		auto OwningTank = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%f: %s: NO aim solution found!"), Time, *OwningTank)
	}
}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurret * TurretToSet)
{
	Turret = TurretToSet;
}

