// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority()) // Only run code on Server
	{
		// Send updates to the client(s)
		SetReplicates(true);
		SetReplicateMovement(true);
	}
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) // Only run code on Server
	{
		// Move the platform (on the server)
		FVector Location = GetActorLocation();
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	}
}