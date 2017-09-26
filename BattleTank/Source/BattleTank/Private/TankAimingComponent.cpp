// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}



void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	auto CurrentTime = GetWorld()->GetTimeSeconds();
	
	if (UGameplayStatics::SuggestProjectileVelocity(this, 
													OUT OutLaunchVelocity, 
													StartLocation, 
													HitLocation, 
													LaunchSpeed, 
													false, 
													0, 
													0, 
													ESuggestProjVelocityTraceOption::DoNotTrace)) {
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!Barrel || !Turret) { return; }

	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}
