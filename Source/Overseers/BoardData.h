// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BoardData.generated.h"

USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardData
{
    GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<AActor*> p_BoardCells;

	UPROPERTY()
	TArray<AActor*> p_BenchCells;

	FBoardData(TArray<AActor*> boardCells, TArray<AActor*> benchCells) : p_BoardCells(boardCells), p_BenchCells(benchCells) {}

	FBoardData() {}
};