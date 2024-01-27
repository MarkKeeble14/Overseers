// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellOccupant.h"
#include "Trait.h"
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
protected:
};
