// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class OVERSEERS_API BoardData
{
public:
	BoardData();
	~BoardData();

	UPROPERTY()
	TArray<AActor*> p_BoardCells;

	UPROPERTY()
	TArray<AActor*> p_BenchCells;

	BoardData(TArray<AActor*> boardCells, TArray<AActor*> benchCells) : p_BoardCells(boardCells), p_BenchCells(benchCells) {}
};
