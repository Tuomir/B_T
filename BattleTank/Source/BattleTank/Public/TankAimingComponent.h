// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel; // Forward declaration

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void Aim(FVector AimLocation, float LaunchSpeed);

	void SetBarrel(UTankBarrel* BarrelToSet);


private:

	UTankBarrel * Barrel = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
};