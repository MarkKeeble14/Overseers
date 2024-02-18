// Fill out your copyright notice in the Description page of Project Settings.

#include "Unit.h"
#include "EngineHelpers.h"
#include "MyPlayerController.h"
#include "GridCell.h"
#include "BoardData.h"

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	m_CurrentHealth = m_MaxHealth;
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_Active) return;

	// if timer has elapsed, take offensive action
	if (m_CurrentTimeBetweenOffensiveActs <= 0)
	{
		TakeOffensiveAct();
	}
	else
	{
		m_CurrentTimeBetweenOffensiveActs -= DeltaTime;
	}
}


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

	combineWith1->Remove(true);
	combineWith2->Remove(true);

	boardData->RemoveUnitFromBoard(this);

	IncrementStage();
	Align();

	boardData->AddUnitToBoard(this);
}

void AUnit::Autoattack(AUnit* target)
{
	if (target == nullptr) return;
	target->TakeDamage(m_AttackDamage, 1);
}

void AUnit::TakeOffensiveAct()
{
	if (m_CurrentResource >= m_MaxResource)
	{
		CastAbility(nullptr);
	}
	else
	{
		Autoattack(nullptr);
	}

	m_CurrentTimeBetweenOffensiveActs = m_TimeBetweenOffensiveActs;
}

void AUnit::CastAbility(AUnit* target)
{
	if (target == nullptr) return;

	// ...
	// m_Ultimate.Cast(target);
}

void AUnit::TakeDamage(float damage, int damageType)
{

	int adjustedDamage;

	if (damageType == 0)
	{
		adjustedDamage = damage - m_Armor;
	}
	else
	{
		adjustedDamage = damage - m_AbilityResistance;
	}
	if (adjustedDamage <= 0) return;

	m_CurrentHealth -= adjustedDamage;
	if (m_CurrentHealth <= 0)
	{
		// Death
		OnDeath.Broadcast(p_BelongsTo->GetPlayerId(), this);

		m_Active = false;
	}
}
