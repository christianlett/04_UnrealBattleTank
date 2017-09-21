// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"




void ATankAIController::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Aim towards player
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!PlayerTank) {
		return;
	}

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	ATank* ControlledTank = Cast<ATank>(GetPawn());
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire when ready!
	ControlledTank->Fire();
}


