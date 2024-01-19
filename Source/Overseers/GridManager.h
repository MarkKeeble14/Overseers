// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoardData.h"
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
	UClass* boardCell;

	UPROPERTY(EditAnywhere)
	UClass* benchCell;

	UPROPERTY(EditAnywhere)
	UClass* boardSeparator;

	UPROPERTY(EditAnywhere)
	float boardSize = 10;

	UPROPERTY(EditAnywhere)
	float benchSize = 10;

	UPROPERTY(EditAnywhere)
	float gridSpacing = 1000;

	UPROPERTY(EditAnywhere)
	float gridCellHeightScale = .25;

	UPROPERTY(EditAnywhere)
	int testMatchupConfiguration = 0;

	UPROPERTY(EditAnywhere)
	FVector color1 = FVector(.1, .1, .1);

	UPROPERTY(EditAnywhere)
	FVector color2 = FVector(.25, .25, .25);

	void MakeGrid(int playerId);

	virtual void BeginPlay() override;

protected:
	TMap<int, BoardData> spawnedGrid;

	TMap<int, AActor*> spawnedBoardSeparators;

	void IncrementBenchPosition(int playerId, FVector* vec, float incBy, int xDir, int yDir);

	void SpawnBoardSeparators();

	AActor* GetRespectiveBoardSeparator(int combatentId1, int combatentId2);

	void SetBoardSeparatorState(bool active, AActor* separator);

	void SetupMatches(int config);
};
