// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming, 
	Locked
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void Aim(FVector AimLocation);

	UFUNCTION(BlueprintCallable)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	

protected:
	UPROPERTY(BlueprintReadOnly, Category = Setup)
	EFiringStatus FiringStatus = EFiringStatus::Locked;

private:

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	float ReloadTimeInSeconds = 3.f;

	double LastFireTime = 0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

	bool BarrelIsMoving();
};
