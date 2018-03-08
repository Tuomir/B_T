// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"

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
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Crosshair direction: %s"), *LookDirection.ToString())

		// Line trace along LookDirection (up to a max range) and see what we hit
		

		if (GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit location: %s"), *OutHitLocation.ToString())
		}
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & OutLookDirection) const
{
	// De-project the screen position of the crosshair to a world direction
	FVector WorldLocation; // To be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, OutLookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = StartLocation + LookDirection * GunRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, LineTraceEnd, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else
	{
		HitLocation = FVector(0.0f);
		return true;
	}

	return false;
}


