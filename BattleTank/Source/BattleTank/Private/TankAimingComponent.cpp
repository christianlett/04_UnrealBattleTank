// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	// TODO should this really tick?

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if (!Barrel) { return; }
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
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solve found"), CurrentTime);

		MoveBarrelTowards(AimDirection);
	} else {
		
		UE_LOG(LogTemp, Error, TEXT("%f: No aim solve found"), CurrentTime);
	}
}


void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// Work out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
//	UE_LOG(LogTemp, Warning, TEXT("DeltaRotator: %s"), *DeltaRotator.ToString());
	
	Barrel->Elevate(5);
}
