// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"


// Enum for aiming state
UENUM()
enum class EFiringStatus : uint8 {
	Reloading,
	Aiming,
	Locked
};

// Forward declarations
class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

private:
	UTankTurret* Turret = nullptr;
	UTankBarrel* Barrel = nullptr;

	

	void MoveBarrelTowards(FVector AimDirection);
	
};
