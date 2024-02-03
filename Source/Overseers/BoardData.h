// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoardUnitStageMapping.h"
#include "BoardTraitMap.h"
#include "BoardData.generated.h"

class AUnit;
class UGridCell;

USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardData
{
    GENERATED_USTRUCT_BODY()

private:

public:
	int m_NumUnitsOnBoard = 0;

	TArray<UGridCell*> p_BoardCells;

	TArray<UGridCell*> p_BenchCells;

	TMap<FString, FBoardUnitStageMapping> m_UnitsOnBoard = {};

	UPROPERTY(BlueprintReadOnly)
	FBoardTraitMap m_TraitsOnBoard;

	FBoardData(TArray<UGridCell*> boardCells, TArray<UGridCell*> benchCells) : p_BoardCells(boardCells), p_BenchCells(benchCells) {}

	FBoardData() {}

	int GetNumUnitsOnBoard() { return m_NumUnitsOnBoard; }

	void AddUnitToBoard(AUnit* unit);

	void RemoveUnitFromBoard(AUnit* unit, int stage);

	UGridCell* GetCellToSpawnOn();
};