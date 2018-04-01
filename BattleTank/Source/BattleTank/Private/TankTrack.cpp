// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}



void UTankTrack::SetThrottle(float Throttle)
{
	// TODO clamp throttle value
	auto ForceApplied = GetForwardVector() * Throttle  * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate slippage speed for sideways friction correction
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// Work out required acceleration this frame to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
	// Calculate and apply sideways force
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = CorrectionAcceleration * TankRoot->GetMass() / 2; // Two tracks
	TankRoot->AddForce(CorrectionForce);
}

