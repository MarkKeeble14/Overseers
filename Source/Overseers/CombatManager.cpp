// Fill out your copyright notice in the Description page of Project Settings.

#include "CombatManager.h"
#include "RoundManager.h"
#include "GridManager.h"
#include "GridCell.h"
#include "Unit.h"
#include "MyPlayerController.h"

// Sets default values
ACombatManager::ACombatManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ACombatManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACombatManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACombatManager::SetupMatch(int playerId1, int playerId2)
{
	// Add to active matches
	m_ActiveMatches.Add(playerId1, playerId2);
	m_ActiveMatches.Add(playerId2, playerId1);

	// Register all units
	RegisterUnitsForCombat(playerId1);
	RegisterUnitsForCombat(playerId2);

	if (m_UnitsInCombat[playerId1].Num() == 0 && m_UnitsInCombat[playerId2].Num() == 0)
	{
		// Tie
		UE_LOG(LogTemp, Warning, TEXT("Tie, Neither Combatent had Units on Board"));

		DeactivateUnitsInMatch(playerId1);

		p_RoundManager->CombatConcluded();
	}
	else if (m_UnitsInCombat[playerId1].Num() == 0)
	{
		// Player 2 Wins
		UE_LOG(LogTemp, Warning, TEXT("Player 2 Wins, Player 1 did not have Units on Board"));

		DeactivateUnitsInMatch(playerId1);

		ApplyDamageResultToPlayer(playerId2, p_GridManager->GetPlayerBoardData(playerId1)->GetPlayerController());

		p_RoundManager->CombatConcluded();
	}
	else if (m_UnitsInCombat[playerId2].Num() == 0)
	{
		// Player 1 Wins
		UE_LOG(LogTemp, Warning, TEXT("Player 1 Wins, Player 2 did not have Units on Board"));

		DeactivateUnitsInMatch(playerId1);

		ApplyDamageResultToPlayer(playerId1, p_GridManager->GetPlayerBoardData(playerId2)->GetPlayerController());

		p_RoundManager->CombatConcluded();
	}
	// Otherwise the combat may proceed normally
}

void ACombatManager::RegisterUnitsForCombat(int playerId)
{
	FBoardData* p1BoardData = p_GridManager->GetPlayerBoardData(playerId);
	TArray<AUnit*> units;

	for (auto it : p1BoardData->p_BoardCells)
	{
		// if cell is not occupied, skip
		if (it->GetIsOccupied())
		{
			ACellOccupant* occupant = it->GetCurrentOccupant();
			AUnit* unit = Cast<AUnit>(occupant);

			// if not a unit, skip
			if (unit == nullptr) continue;

			units.Add(unit);

			unit->Activate();

			unit->OnDeath.AddDynamic(this, &ACombatManager::UnregisterUnitForCombat);
		}
	}
	m_UnitsInCombat.Add(playerId, units);
}

void ACombatManager::UnregisterUnitForCombat(int playerId, AUnit* unit)
{
	m_UnitsInCombat[playerId].Remove(unit);

	// also need to unbind function to an on death event on unit
	unit->OnDeath.RemoveDynamic(this, &ACombatManager::UnregisterUnitForCombat);

	if (m_UnitsInCombat[playerId].Num() == 0)
	{
		DeactivateUnitsInMatch(playerId);

		int winnerId = m_ActiveMatches[playerId];

		ApplyDamageResultToPlayer(winnerId, p_GridManager->GetPlayerBoardData(playerId)->GetPlayerController());

		p_RoundManager->CombatConcluded();
	}
}

void ACombatManager::DeactivateUnitsInMatch(int participatingPlayerId)
{
	int player2Id = m_ActiveMatches[participatingPlayerId];
	for (auto it : m_UnitsInCombat[participatingPlayerId])
	{
		it->Deactivate();
	}

	for (auto it : m_UnitsInCombat[player2Id])
	{
		it->Deactivate();
	}
}

void ACombatManager::ActivateUnitsInMatch(int participatingPlayerId)
{
	int player2Id = m_ActiveMatches[participatingPlayerId];
	for (auto it : m_UnitsInCombat[participatingPlayerId])
	{
		it->Activate();
	}

	for (auto it : m_UnitsInCombat[player2Id])
	{
		it->Activate();
	}
}

void ACombatManager::ApplyDamageResultToPlayer(int winnerId, AMyPlayerController* damagingPlayer)
{
	if (damagingPlayer == nullptr) return;

	int numUnits = 0;
	for (auto it : m_UnitsInCombat[winnerId])
	{
		numUnits += it->GetStage();
	}

	damagingPlayer->AlterGameHP(numUnits * m_DamagePerUnitOnRoundLoss * -1);
}

void ACombatManager::Reset()
{
	for (TPair<int, TArray<AUnit*>>& pair : m_UnitsInCombat)
	{
		for (auto it : pair.Value)
		{
			it->Deactivate();

			// also need to unbind function to an on death event on unit
			it->OnDeath.RemoveDynamic(this, &ACombatManager::UnregisterUnitForCombat);
		}
	}

	m_ActiveMatches.Empty();
	m_UnitsInCombat.Empty();
}