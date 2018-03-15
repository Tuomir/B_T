// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming component"));

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->Aim(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	// Aiming component's barrel reference
	TankAimingComponent->SetBarrel(BarrelToSet);

	// Local reference for barrel
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
	if (!Barrel) { return; }

	auto SpawnLocation = Barrel->GetSocketLocation(FName("Projectile"));
	auto SpawnRotation = Barrel->GetSocketRotation(FName("Projectile"));

	// Spawn a projectile from the end of the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint, SpawnLocation, SpawnRotation);

	// Launch projectile
	Projectile->LaunchProjectile(LaunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

