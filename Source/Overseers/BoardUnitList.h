// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardUnitList.generated.h"

class AUnit;

/**
 * 
 */

USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardUnitList
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AUnit*> m_List = {};

	int Num() { return m_List.Num(); }

	AUnit* Get(int index) { return m_List[index]; }

	void Add(AUnit* unit);

	void Remove(AUnit* unit);
};