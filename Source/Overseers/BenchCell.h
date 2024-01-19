// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "BenchCell.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OVERSEERS_API UBenchCell : public UGridCell
{
	GENERATED_BODY()

public:
	UBenchCell();
	~UBenchCell();
};
