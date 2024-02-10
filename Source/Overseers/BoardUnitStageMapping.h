// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardUnitList.h"
#include "BoardUnitStageMapping.generated.h"

class AUnit;

/**
 * 
 */
USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardUnitStageMapping
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, FBoardUnitList> m_UnitsOfEachStage = {};

	FBoardUnitStageMapping(TArray<AUnit*> units);

	FBoardUnitStageMapping() {}

	void Add(AUnit* unit, int addTo);

	void Remove(AUnit* unit, int removeFrom);

	int GetNumberOfUnits();
};
