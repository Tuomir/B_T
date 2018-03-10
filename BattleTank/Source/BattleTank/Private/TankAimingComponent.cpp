// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
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

	auto OwningTank = GetOwner()->GetName();

	
	// Elevate barrel
	Barrel->Elevate(5.f); // TODO remove magic number

}

void UTankAimingComponent::Aim(FVector AimLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	auto OwningTank = GetOwner()->GetName();

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, AimLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();

		MoveBarrelTowards(AimLocation);
		
		// Find Turret mesh
		// Rotate turret azimuth

		

		
	}

}

void UTankAimingComponent::SetBarrel(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

