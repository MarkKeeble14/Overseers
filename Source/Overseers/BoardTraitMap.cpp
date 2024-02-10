// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardTraitMap.h"
#include "MyCharacter.h"
#include "GridManager.h"

ETrait FBoardTraitMap::Add(ETrait trait)
{
	if (m_TraitCounts.Contains(trait))
	{
		m_TraitCounts[trait] = m_TraitCounts[trait] + 1;
	}
	else
	{
		m_TraitCounts.Add(trait, 1);
	}

	p_Representing->OnTraitAddedToBoard.Broadcast(trait);

	// Figure out if should activate trait
	// Return the activated trait
	if (p_Representing->DidChangeTraitBreakpointRegion(trait, m_TraitCounts[trait] - 1, m_TraitCounts[trait]))
	{
		return trait;
	}


	return ETrait::T_None;
}

ETrait FBoardTraitMap::Remove(ETrait trait)
{
	if (m_TraitCounts.Contains(trait))
	{
		m_TraitCounts[trait] = m_TraitCounts[trait] - 1;
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to Remove Trait that was not found in Map: %d"), trait);
	}

	p_Representing->OnTraitRemovedFromBoard.Broadcast(trait);

	// Figure out if should deactivate trait
	// Return the deactivated trait
	if (p_Representing->DidChangeTraitBreakpointRegion(trait, m_TraitCounts[trait] + 1, m_TraitCounts[trait]))
	{
		return trait;
	}

	return ETrait::T_None;
}

void FBoardTraitMap::LogState()
{
	UE_LOG(LogTemp, Warning, TEXT("Logging State (Trait Map)"));
	for (TPair<ETrait, int>& pair : m_TraitCounts)
	{
		FString s = UEnum::GetValueAsString(pair.Key);
		UE_LOG(LogTemp, Warning, TEXT("%s: %d"), *s, pair.Value);
	}
}