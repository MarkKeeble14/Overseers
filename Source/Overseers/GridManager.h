// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoardData.h"
#include "CharacterBoardVisuals.h"
#include "GridManager.generated.h"

/**
 * 
 */
UCLASS()
class OVERSEERS_API AGridManager : public AActor
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TMap<int, FBoardData> spawnedGrid;

	TMap<int, AActor*> spawnedBoardSeparators;

	void IncrementBenchPosition(int playerId, FVector* vec, float incBy, int xDir, int yDir);

	void SpawnBorderWall(int playerId);

	AActor* GetRespectiveBoardSeparator(int combatentId1, int combatentId2);

	void SetBoardSeparatorState(bool active, AActor* separator);

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

	FBoardData* GetPlayerBoardData(int playerId)
	{
		if (!spawnedGrid.Contains(playerId)) return nullptr;
		return &spawnedGrid[playerId];
	}

	UFUNCTION(BlueprintCallable)
	FBoardData GetCopyOfPlayerBoardData(int playerId)
	{
		if (!spawnedGrid.Contains(playerId)) return FBoardData();
		return *GetPlayerBoardData(playerId);
	}

	UFUNCTION(BlueprintCallable)
	int GetPlayerSpawnPosition()
	{
		return boardSize * gridSpacing * 0.9;
	}

	UFUNCTION(BlueprintCallable)
	void SetupMatches(int config);

	UFUNCTION(BlueprintCallable)
	void SpawnBoardSeparators();

	UFUNCTION(BlueprintCallable)
	void MakeGrid(int playerId);

	UFUNCTION(BlueprintCallable)
	void ClearBoard();

	UFUNCTION(BlueprintCallable)
	void AttachPlayerToBoardData(int playerId, AMyPlayerController* player);

	UFUNCTION(BlueprintCallable)
	void SetCharacterBounds(AMyCharacter* character);
};
