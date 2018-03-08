// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s controlled by player controller"), *GetControlledTank()->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrossHair();

	//UE_LOG(LogTemp, Warning, TEXT("Player controller says: Tick!"))
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation; // Out parameter
	if (GetSightRayHitLocation(OutHitLocation)) // Side effect: line tracing
	{
		//UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *OutHitLocation.ToString())
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & OutHitLocation) const
{
	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	UE_LOG(LogTemp, Warning, TEXT("Crosshair screen location: %s"), *ScreenLocation.ToString())

	OutHitLocation = FVector(1.0f);
	return false;
}


