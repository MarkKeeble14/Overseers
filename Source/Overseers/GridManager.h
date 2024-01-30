// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardData.h"
#include "GridCell.h"
#include "CharacterBoardVisuals.h"
#include "GridManager.generated.h"

/**
 * 
 */
UCLASS()
class OVERSEERS_API AGridManager : public AActor
{
	GENERATED_BODY()

public:
	AGridManager();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	int m_StartingSeparatorConfig = 0;

	UPROPERTY(EditAnywhere)
	TMap<int, FCharacterBoardVisuals> m_PlayerGridVisuals;

	void MakeGrid(int playerId);

	void SetupMatches(int config);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TMap<int, FBoardData> spawnedGrid;

	TMap<int, AActor*> spawnedBoardSeparators;

	void IncrementBenchPosition(int playerId, FVector* vec, float incBy, int xDir, int yDir);

	void SpawnBoardSeparators();

	AActor* GetRespectiveBoardSeparator(int combatentId1, int combatentId2);

	void SetBoardSeparatorState(bool active, AActor* separator);
};
