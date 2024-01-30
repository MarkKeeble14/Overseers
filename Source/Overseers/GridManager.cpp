// Fill out your copyright notice in the Description page of Project Settings.

#include "GridManager.h"

AGridManager::AGridManager()
{
}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 4; i++)
	{
		MakeGrid(i);
	}

	SpawnBoardSeparators();

	SetupMatches(m_StartingSeparatorConfig);
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridManager::MakeGrid(int playerId)
{
	if (boardCell == nullptr || benchCell == nullptr) return;

	// These numbers adjust the direction that cells are spawned in
	int xDir = 1;
	if (playerId == 2 || playerId == 3)
		xDir = -1;
	
	int yDir = 1;
	if (playerId == 1 || playerId == 2)
		yDir = -1;

	// Init spawnPos
	FVector spawnPos = FVector(gridSpacing / 2 * xDir, gridSpacing / 2 * yDir, 0);

	const FVector cellScale = FVector(gridSpacing / 100, gridSpacing / 100, gridCellHeightScale);
	AActor* spawned = nullptr;
	TArray<AActor*> spawnedBoardCells;
	TArray<AActor*> spawnedBenchCells;

	// Spawn Cells
	for (int i = 0; i < boardSize; i++)
	{
		for (int p = 0; p < boardSize; p++)
		{
			spawned = GetWorld()->SpawnActor(boardCell, &spawnPos);
			spawned->SetActorScale3D(cellScale);

			// Set Color
			UGridCell* spawnedCell = spawned->GetComponentByClass<UGridCell>();
			if (spawnedCell != nullptr)
			{
				spawnedCell->SetDefaultColor((i + p) % 2 == 0 ? m_PlayerGridVisuals[playerId].m_Color1 : m_PlayerGridVisuals[playerId].m_Color2);
			}

			spawnedBoardCells.Add(spawned);

			// Set owned by
			spawnedCell->SetOwnedByPlayerId(playerId);

			spawnPos.X += gridSpacing * xDir;
		}
		spawnPos.Y += gridSpacing * yDir;
		spawnPos.X -= gridSpacing * xDir * boardSize;
	}

	// Create Bench
	// Determine where to start spawning
	spawnPos.X = gridSpacing * xDir * boardSize + (gridSpacing / 2 * xDir);
	spawnPos.Y = gridSpacing * yDir * boardSize + (gridSpacing / 2 * yDir);
	IncrementBenchPosition(playerId, &spawnPos, gridSpacing, xDir, yDir);
	for (int i = 0; i < (boardSize - benchSize) / 2; i++)
		IncrementBenchPosition(playerId, &spawnPos, gridSpacing, xDir, yDir);

	// Spawn Bench Cells
	for (int i = 0; i < benchSize; i++)
	{
		spawned = GetWorld()->SpawnActor(benchCell, &spawnPos);
		UGridCell* spawnedCell = spawned->GetComponentByClass<UGridCell>();
		spawned->SetActorScale3D(cellScale);

		spawnedCell->SetDefaultColor(m_PlayerGridVisuals[playerId].m_Color1);

		IncrementBenchPosition(playerId, &spawnPos, gridSpacing, xDir, yDir);
		spawnedBenchCells.Add(spawned);

		spawnedCell->SetOwnedByPlayerId(playerId);
	}

	// Insert newly spawned board into map
	spawnedGrid.Add(playerId, FBoardData{spawnedBoardCells, spawnedBenchCells});
}

void AGridManager::IncrementBenchPosition(int playerId, FVector* vec, float incBy, int xDir, int yDir)
{
	switch (playerId)
	{
		case 0:
			vec->X -= incBy * xDir;
			break;
		case 1:
			vec->Y -= incBy * yDir;
			break;
		case 2:
			vec->X -= incBy * xDir;
			break;
		case 3:
			vec->Y -= incBy * yDir;
			break;
		default:
			break;
	}
}

void AGridManager::SpawnBoardSeparators()
{
	if (boardSeparator == nullptr) return;

	AActor* spawned = nullptr;
	const int distFromOrigin = boardSize * gridSpacing / 2;
	const FVector wallScale = FVector(gridSpacing / 100 * boardSize, 1, gridSpacing / 100 * boardSize);
	FVector spawnPos;
	FRotator spawnRot;
	for (int i = 0; i < 4; i++)
	{	
		switch (i)
		{
			case 0:
				spawnPos = FVector(distFromOrigin, 0, 0);
				spawnRot = FRotator(0, 0, 0);
				break;
			case 1:
				spawnPos = FVector(0, -distFromOrigin, 0);
				spawnRot = FRotator(0, 90, 0);
				break;
			case 2:
				spawnPos = FVector(-distFromOrigin, 0, 0);
				spawnRot = FRotator(0, 0, 0);
				break;
			case 3:
				spawnPos = FVector(0, distFromOrigin, 0);
				spawnRot = FRotator(0, 90, 0);
				break;
		}

		spawned = GetWorld()->SpawnActor(boardSeparator, &spawnPos, &spawnRot);
		spawned->SetActorScale3D(wallScale);
		spawnedBoardSeparators.Add(i, spawned);
	}
}

AActor* AGridManager::GetRespectiveBoardSeparator(int combatentId1, int combatentId2)
{
	// Player Id 0
	if (combatentId1 == 0 && combatentId2 == 1)
		return spawnedBoardSeparators[0];
	else if (combatentId1 == 0 && combatentId2 == 3)
		return spawnedBoardSeparators[3];

	// Player Id 1
	else if (combatentId1 == 1 && combatentId2 == 0)
		return spawnedBoardSeparators[0];
	else if (combatentId1 == 1 && combatentId2 == 2)
		return spawnedBoardSeparators[1];

	// Player Id 2
	else if (combatentId1 == 2 && combatentId2 == 1)
		return spawnedBoardSeparators[1];
	else if (combatentId1 == 2 && combatentId2 == 3)
		return spawnedBoardSeparators[2];

	// Player Id 3
	else if (combatentId1 == 3 && combatentId2 == 2)
		return spawnedBoardSeparators[2];
	else if (combatentId1 == 3 && combatentId2 == 0)
		return spawnedBoardSeparators[3];

	return nullptr;
}

void AGridManager::SetupMatches(int config)
{
	switch (config)
	{
		case 0:
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(0, 1));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(3, 2));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(0, 3));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(1, 2));
			break;
		case 1:
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(0, 1));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(3, 2));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(0, 3));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(1, 2));
			break;
		case 2:
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(0, 1));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(3, 2));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(0, 3));
			SetBoardSeparatorState(true, GetRespectiveBoardSeparator(1, 2));
		case 3:
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(0, 1));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(3, 2));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(0, 3));
			SetBoardSeparatorState(false, GetRespectiveBoardSeparator(1, 2));
		default:
			break;
	}
}

void AGridManager::SetBoardSeparatorState(bool active, AActor* separator)
{
	if (separator == nullptr) return;
	separator->SetActorEnableCollision(!active);
	separator->SetActorHiddenInGame(active);
}