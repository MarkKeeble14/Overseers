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
	if (m_UnitsOnBoard.Contains(unitName))
	{
		// Add Unit
		m_UnitsOnBoard[unitName].Add(unit);

		// If we have just added a unit that did not previously exist onto the board, we add it's traits
		if (m_UnitsOnBoard[unitName].GetTotalNumOfUnit() == 1)
		{
			for (ETrait t : unit->GetData().m_Traits)
			{
				ETrait activatedTrait = m_TraitsOnBoard.Add(t);
				if (activatedTrait != ETrait::T_None)
				{
					// Activate Trait
				}
			}
		}
	}
	else
	{
		// Add Unit
		m_UnitsOnBoard.Add(unitName, FBoardUnitStageMapping({ unit }));

		// Add Traits
		for (ETrait t : unit->GetData().m_Traits)
		{
			ETrait activatedTrait = m_TraitsOnBoard.Add(t);
			if (activatedTrait != ETrait::T_None)
			{
				// Activate Trait
			}
		}
	}

	UGridCell* cell = unit->GetCellUnderneath();
	if (cell->GetCountsTowardUnitMax())
	{
		m_NumUnitsOnBoard++;
	}
}

void FBoardData::RemoveUnitFromBoard(AUnit* unit, int stage)
{
	FString unitName = unit->GetData().m_Name;
	if (m_UnitsOnBoard.Contains(unitName))
	{
		// Remove Unit
		m_UnitsOnBoard[unitName].Remove(unit, stage);

		// Remove Traits if there are no more instances of that unit on the board
		if (m_UnitsOnBoard[unitName].GetTotalNumOfUnit() == 0)
		{
			for (ETrait t : unit->GetData().m_Traits)
			{
				ETrait deactivatedTrait = m_TraitsOnBoard.Remove(t);
				if (deactivatedTrait != ETrait::T_None)
				{
					// Deactivate Trait
				}
			}
		}

		UGridCell* cell = unit->GetCellUnderneath();
		if (cell->GetCountsTowardUnitMax())
		{
			m_NumUnitsOnBoard--;
		}
	}
	else
	{
		// wtf happened broski
		UE_LOG(LogTemp, Warning, TEXT("Tried to remove a unit that supposedly did not exist on board"));
	}
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
