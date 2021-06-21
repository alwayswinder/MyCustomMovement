// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYCUSTOMMOVEMENT_API UMyCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyCustomMovement")
	bool IsJetting;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCustomMovement")
	bool IsGravityOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCustomMovement")
	FVector AddVelocity;

	virtual FVector NewFallVelocity(const FVector& InitialVelocity, const FVector& Gravity, float DeltaTime) const override;
	virtual void ApplyDownwardForce(float DeltaSeconds)override;

	
};
