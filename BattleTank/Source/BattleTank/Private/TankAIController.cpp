// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* MyTank = GetPlayerTank();

	if (!MyTank) {
		UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AIController found player %s"), *(MyTank->GetName()));
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim towards player
	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank) {
		return;
	}
	GetControlledTank()->AimAt(PlayerTank->GetActorLocation());

	// Fire when ready!
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {
		return nullptr;
	}

	return Cast<ATank>(PlayerPawn);
	
}

