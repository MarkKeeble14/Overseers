// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"
#include "GridCell.h"
#include "EngineHelpers.h"

void AUnit::IncrementStage()
{
	if (m_Stage >= m_MaxStage) return; 
	m_Stage++;
	SetScaleBasedOnStage();
}

void AUnit::SetScaleBasedOnStage()
{
	UGridCell* cell = GetCellUnderneath();
	if (cell == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Cell Underneath (SetScaleBasedOnStage)"));
		return;
	}
	AActor* cellActor = cell->GetOwner();

	// Set Scale
	float scale = cellActor->GetActorScale().X / (4 - m_Stage) - 2.5;
	SetActorScale3D(FVector(scale, scale, scale));
}

void AUnit::Combine(AUnit* combineWith1, AUnit* combineWith2)
{
	FBoardData* boardData = p_BelongsTo->GetPlayerBoardData();

	combineWith1->Remove();
	combineWith2->Remove();

	IncrementStage();
	Align();
	
	boardData->RemoveUnitFromBoard(this, m_Stage - 1);
	boardData->AddUnitToBoard(this);
}
