// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridCell.h"
#include "GridManager.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class OVERSEERS_API UGridManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UGridManager();
	~UGridManager();

	UPROPERTY(EditAnywhere)
	UClass* gridCell;

	UPROPERTY(EditAnywhere)
	float gridSize = 10;

	UPROPERTY(EditAnywhere)
	float gridSpacing = 1000;

	UPROPERTY(EditAnywhere)
	float gridCellHeightScale = .25;

	UPROPERTY(EditAnywhere)
	FVector color1 = FVector(.1, .1, .1);

	UPROPERTY(EditAnywhere)
	FVector color2 = FVector(.25, .25, .25);

	void PopulateGrid();

	virtual void BeginPlay() override;

protected:
	std::vector<AActor*> spawnedGrid;
	int numGridsSpawned;
};
