// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterMovementComponent.h"
#include "GameFramework/PhysicsVolume.h"


FVector UMyCharacterMovementComponent::NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const
{
	FVector FinalGravity = Gravity;
	if (IsJetting)
	{
		FinalGravity += AddVelocity;
	}
	if (IsGravityOverride)
	{
		FinalGravity = AddVelocity;
	}

	FVector Result = InitialVelocity;

	if (DeltaTime > 0.f)
	{
		// Apply gravity.
		Result += FinalGravity * DeltaTime;

		// Don't exceed terminal velocity.
		const float TerminalLimit = FMath::Abs(GetPhysicsVolume()->TerminalVelocity);
		if (Result.SizeSquared() > FMath::Square(TerminalLimit))
		{
			const FVector GravityDir = FinalGravity.GetSafeNormal();
			if ((Result | GravityDir) > TerminalLimit)
			{
				Result = FVector::PointPlaneProject(Result, FVector::ZeroVector, GravityDir) + GravityDir * TerminalLimit;
			}
		}
	}
	return Result;
}

void UMyCharacterMovementComponent::ApplyDownwardForce(float DeltaSeconds)
{
	FVector FinalGravity = FVector(0.0f, 0.0f, GetGravityZ());
	if (IsGravityOverride)
	{
		FinalGravity = AddVelocity;
	}
	if (StandingDownwardForceScale != 0.0f && CurrentFloor.HitResult.IsValidBlockingHit())
	{
		UPrimitiveComponent* BaseComp = CurrentFloor.HitResult.GetComponent();

		if (BaseComp && BaseComp->IsAnySimulatingPhysics() && !FinalGravity.IsZero())
		{
			BaseComp->AddForceAtLocation(FinalGravity * Mass * StandingDownwardForceScale, CurrentFloor.HitResult.ImpactPoint, CurrentFloor.HitResult.BoneName);
		}
	}
}
