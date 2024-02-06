// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNetworkManager.h"
#include <Net/UnrealNetwork.h>

// Sets default values
AMyNetworkManager::AMyNetworkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AMyNetworkManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyNetworkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyNetworkManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(AMyNetworkManager, Owner);
}

void AMyNetworkManager::IncrementNextPlayerIndex()
{
	m_NextPlayerIndex += 1;
}