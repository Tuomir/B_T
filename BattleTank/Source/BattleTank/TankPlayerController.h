// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
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



	UPROPERTY(EditAnyWhere)
	float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnyWhere)
	float CrossHairYLocation = 0.33333f;
};
