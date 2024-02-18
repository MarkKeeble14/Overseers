// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "TraitsManager.h"
#include "GridManager.h"
#include "Trait.h"
#include "BoardData.h"

// Called when the game starts or when spawned
void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerGameHP = m_MaxPlayerGameHP;
}

bool AMyPlayerController::AlterGameHP(float amount)
{
	UE_LOG(LogTemp, Warning, TEXT("Alter Game HP Called (%d)"), amount);
	/*
	if (m_PlayerGameHP + amount < 0)
	{
		m_PlayerGameHP = 0;
		return true;
	}
	else if (m_PlayerGameHP + amount > m_MaxPlayerGameHP)
	{
		m_PlayerGameHP = m_MaxPlayerGameHP;
	}
	else
	{
		m_PlayerGameHP += amount;
	}
	UE_LOG(LogTemp, Warning, TEXT("New Player Game HP: %d"), m_PlayerGameHP);
	*/
	return false;
}

FBoardData* AMyPlayerController::GetPlayerBoardData()
{
	return p_GridManager->GetPlayerBoardData(m_PlayerId);
}

bool AMyPlayerController::DidChangeTraitBreakpointRegion(ETrait trait, int previous, int current)
{
	if (p_TraitsManager == nullptr)
	{
		return false;
	}

	if (previous > current)
	{
		// Decreased
		int lastBreakpoint = p_TraitsManager->GetLastBreakpoint(trait, previous);
		return lastBreakpoint == current;
	}
	else if (current > previous)
	{
		// Increased
		if (p_TraitsManager->IsMaxBreakpoint(trait, current)) return false;
		int nextBreakpoint = p_TraitsManager->GetNextBreakpoint(trait, previous);
		return nextBreakpoint == current;
	}

	return false;
}