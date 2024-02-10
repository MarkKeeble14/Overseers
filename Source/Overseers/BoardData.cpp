// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardData.h"
#include "Unit.h"
#include "GridCell.h"

void FBoardData::AddUnitToBoard(AUnit* unit)
{
	if (unit == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add a nullptr to board"));
		return;
	}

	FString unitName = unit->GetData().m_Name;
	UE_LOG(LogTemp, Warning, TEXT("Adding Unit to Board: %s"), *unitName);

	if (!m_UnitsOnBoard.Contains(unitName))
	{
		m_UnitsOnBoard.Add(unitName, FBoardUnitStageMapping());
	}

	// Add Unit
	m_UnitsOnBoard[unitName].Add(unit, unit->GetStage());

	UGridCell* cell = unit->GetCellUnderneath();
	if (cell->GetCountsTowardUnitMax())
	{
		m_NumUnitsOnBoard++;

		// If we are adding a unit that did not previously exist onto the board, we add it's traits
		if (!UnitTypeIsContributingToTraits(unit))
		{
			UE_LOG(LogTemp, Warning, TEXT("Adding Traits for Unit: %s"), *unitName);

			m_ContributingToTraits.Add(unit);

			for (ETrait t : unit->GetData().m_Traits)
			{
				ETrait activatedTrait = m_TraitsOnBoard.Add(t);
				if (activatedTrait != ETrait::T_None)
				{
					// Change Trait Activation Region
					UE_LOG(LogTemp, Warning, TEXT("Change Trait Activation Region"));
				}
			}
		}
	}
}

void FBoardData::RemoveUnitFromBoard(AUnit* unit)
{
	FString unitName = unit->GetData().m_Name;
	UE_LOG(LogTemp, Warning, TEXT("Removing Unit to Board: %s"), *unitName);

	if (!m_UnitsOnBoard.Contains(unitName))
	{
		// wtf happened broski
		UE_LOG(LogTemp, Warning, TEXT("Tried to remove a unit that supposedly did not exist on board"));
		return;
	}

	// Remove Unit
	m_UnitsOnBoard[unitName].Remove(unit, unit->GetStage());

	// Remove Traits if there are no more instances of that unit on the board
	if (m_ContributingToTraits.Contains(unit))
	{
		UE_LOG(LogTemp, Warning, TEXT("Removing Traits for Unit: %s"), *unitName);

		for (ETrait t : unit->GetData().m_Traits)
		{
			ETrait deactivatedTrait = m_TraitsOnBoard.Remove(t);
			if (deactivatedTrait != ETrait::T_None)
			{
				// Change Trait Activation Region
				UE_LOG(LogTemp, Warning, TEXT("Change Trait Activation Region"));
			}
		}

		m_ContributingToTraits.Remove(unit);
	}

	UGridCell* cell = unit->GetCellUnderneath();
	if (cell->GetCountsTowardUnitMax())
	{
		m_NumUnitsOnBoard--;
	}
}

void FBoardData::UpdateUnitStage(AUnit* unit, int oldStage, int newStage)
{
	if (oldStage == newStage) return;
	if (unit == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to add a nullptr to board"));
		return;
	}

	FString unitName = unit->GetData().m_Name;
	UE_LOG(LogTemp, Warning, TEXT("Updating Unit Stage: %s"), *unitName);

	m_UnitsOnBoard[unitName].Remove(unit, oldStage);
	m_UnitsOnBoard[unitName].Add(unit, newStage);
}


UGridCell* FBoardData::GetCellToSpawnOn()
{
	// Look through bench cells
	for (auto it : p_BenchCells)
	{
		if (!it->GetIsOccupied())
			return it;
	}

	// Look through board cells
	for (auto it : p_BoardCells)
	{
		if (!it->GetIsOccupied())
			return it;
	}

	return nullptr;
}

bool FBoardData::UnitTypeIsContributingToTraits(AUnit* unit)
{
	for (auto it : m_ContributingToTraits)
	{
		if (it->GetData().m_Name == unit->GetData().m_Name)
			return true;
	}
	return false;
}
