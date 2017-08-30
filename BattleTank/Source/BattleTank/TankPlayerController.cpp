// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* MyTank = GetControlledTank();

	if (!MyTank) {
		UE_LOG(LogTemp, Error, TEXT("PlayerController not posessing a tank"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play with Tank %s"), *(MyTank->GetName()));
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	// Get world location by linetracing through crosshair
	// If it hits the landscape
		// Tell controlled tank to aim at this point
}