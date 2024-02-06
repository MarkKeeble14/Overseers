// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellOccupant.h"
#include "UnitInfo.h"
#include "Unit.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class OVERSEERS_API AUnit : public ACellOccupant
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FUnitInfo data;

	UFUNCTION(BlueprintCallable)
	FUnitInfo GetData() { return data; }

	void IncrementStage();

	UFUNCTION(BlueprintCallable)
	int GetStage() { return m_Stage; }

	UFUNCTION(BlueprintCallable)
	int GetValue() { return FMath::Pow((float)data.m_Rarity, (float)m_Stage + 1); }

	// Uses Stage
	void SetScaleBasedOnStage();

	void Combine(AUnit* combineWith1, AUnit* combineWith2);
protected:
private:
	int m_Stage = 1;

	int m_MaxStage = 3;
};
