// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "BoardCell.generated.h"

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OVERSEERS_API UBoardCell : public UGridCell
{
	GENERATED_BODY()

public:
	UBoardCell();
	~UBoardCell();
};
