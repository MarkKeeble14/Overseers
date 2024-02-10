// Fill out your copyright notice in the Description page of Project Settings.


#include "TraitsManager.h"

// Sets default values
ATraitsManager::ATraitsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATraitsManager::BeginPlay()
{
	Super::BeginPlay();

	InitializeTraitBreakpoints();
}

// Called every frame
void ATraitsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int ATraitsManager::GetNextBreakpoint(ETrait trait, int current)
{
	if (!m_TraitActivationBreakpoints.Contains(trait))
		return 999;
	TArray traitBreakpoints = m_TraitActivationBreakpoints[trait];
	for (int i = 0; i < traitBreakpoints.Num(); i++)
	{
		if (traitBreakpoints[i] > current) return traitBreakpoints[i];
	}
	return traitBreakpoints[traitBreakpoints.Num() - 1];
}

int ATraitsManager::GetLastBreakpoint(ETrait trait, int current)
{
	if (!m_TraitActivationBreakpoints.Contains(trait))
		return 999;
	TArray traitBreakpoints = m_TraitActivationBreakpoints[trait];
	for (int i = traitBreakpoints.Num() - 1; i > 0; i--)
	{
		if (traitBreakpoints[i] < current) return traitBreakpoints[i];
	}
	return traitBreakpoints[0];
}

bool ATraitsManager::IsMaxBreakpoint(ETrait trait, int current)
{
	if (!m_TraitActivationBreakpoints.Contains(trait))
		return false;
	TArray traitBreakpoints = m_TraitActivationBreakpoints[trait];
	return current == traitBreakpoints[traitBreakpoints.Num() - 1];
}

void ATraitsManager::InitializeTraitBreakpoints()
{
	// Fire
	m_TraitActivationBreakpoints.Add(ETrait::T_Fire, {3, 6, 9});

	// Water
	m_TraitActivationBreakpoints.Add(ETrait::T_Water, { 2, 4, 6 });

	// Air
	m_TraitActivationBreakpoints.Add(ETrait::T_Air, { 1, 2, 3 });

	// Earth
	m_TraitActivationBreakpoints.Add(ETrait::T_Earth, { 4, 5, 6 });
}

