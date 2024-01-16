// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OVERSEERS_API UGridCell : public UActorComponent
{
	GENERATED_BODY()

public:
	UGridCell();
	~UGridCell();
};
