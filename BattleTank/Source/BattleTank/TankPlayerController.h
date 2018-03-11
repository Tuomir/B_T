// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	ATank * GetControlledTank() const;

	void AimTowardsCrossHair();

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection ,FVector& HitLocation) const;

	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnyWhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(EditAnyWhere)
	float GunRange = 1000000.0f;
};
