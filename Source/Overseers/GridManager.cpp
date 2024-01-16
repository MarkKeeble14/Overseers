// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"

UGridManager::UGridManager()
{
}

UGridManager::~UGridManager()
{
}

void UGridManager::PopulateGrid()
{
	int xDir = 1;
	if (numGridsSpawned == 2 || numGridsSpawned == 3)
		xDir = -1;
	
	int yDir = 1;
	if (numGridsSpawned == 1 || numGridsSpawned == 2)
		yDir = -1;

	// Init spawnPos
	FVector spawnPos = FVector(gridSpacing / 2 * xDir, gridSpacing / 2 * yDir, 0);
	
	// Clear
	spawnedGrid.clear();

	const FVector cellScale = FVector(gridSpacing / 100, gridSpacing / 100, gridCellHeightScale);
	for (int i = 0; i < gridSize; i++)
	{
		for (int p = 0; p < gridSize; p++)
		{
			AActor* spawned =  GetWorld()->SpawnActor(gridCell, &spawnPos);
			spawned->SetActorScale3D(cellScale);

			UStaticMeshComponent* mesh = spawned->GetComponentByClass<UStaticMeshComponent>();
			UMaterialInstanceDynamic* material = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), NULL);
			material->SetVectorParameterValue("BaseColor", (i + p) % 2 == 0 ? color1 : color2);
			mesh->SetMaterial(0, material);

			// spawnedGrid.push_back(spawned);
			spawnPos.X += gridSpacing * xDir;
		}
		spawnPos.Y += gridSpacing * yDir;
		spawnPos.X -= gridSpacing * xDir * gridSize;
	}

	numGridsSpawned++;
}

void UGridManager::BeginPlay()
{
	Super::BeginPlay();
	
	PopulateGrid();
	PopulateGrid();
	PopulateGrid();
	PopulateGrid();
}