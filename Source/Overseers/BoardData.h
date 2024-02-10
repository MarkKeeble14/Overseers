// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoardUnitStageMapping.h"
#include "BoardTraitMap.h"
#include "BoardData.generated.h"

class AUnit;
class UGridCell;
class AGridManager;

USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardData
{
    GENERATED_USTRUCT_BODY()

private:
	int m_BelongsTo;

	AMyCharacter* p_Representing;

public:
	int m_NumUnitsOnBoard = 0;

	TArray<UGridCell*> p_BoardCells;

	TArray<UGridCell*> p_BenchCells;

	UPROPERTY(BlueprintReadOnly)
	FBoardTraitMap m_TraitsOnBoard;

	TMap<FString, FBoardUnitStageMapping> m_UnitsOnBoard = {};

	TArray<AUnit*> m_ContributingToTraits = {};

	FBoardData(TArray<UGridCell*> boardCells, TArray<UGridCell*> benchCells, int playerId, AGridManager* gridManager) 
		: p_BoardCells(boardCells), p_BenchCells(benchCells), m_BelongsTo(playerId)
	{
		m_TraitsOnBoard = FBoardTraitMap();
	}

	FBoardData() {}

	void AttatchPlayer(AMyCharacter* character)
	{
		m_TraitsOnBoard.AttachCharacter(character);
	}

	int GetNumUnitsOnBoard() { return m_NumUnitsOnBoard; }

	void AddUnitToBoard(AUnit* unit);

	void RemoveUnitFromBoard(AUnit* unit);

	void UpdateUnitStage(AUnit* unit, int oldStage, int newStage);

	bool UnitTypeIsContributingToTraits(AUnit* unit);

	UGridCell* GetCellToSpawnOn();
};