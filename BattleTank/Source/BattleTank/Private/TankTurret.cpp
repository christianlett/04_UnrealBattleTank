// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "UnrealMathUtility.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Clamp RelativeSpeed to between -1 and 1
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}


