// Fill out your copyright notice in the Description page of Project Settings.


#include "BoardTraitMap.h"
#include "MyCharacter.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Added Trait: %d - %d"), trait, m_TraitCounts[trait]);

	// p_Representing->SetTraitsUI();

	/*
	if (m_TraitCounts[trait] > 5)
	{
		return trait;
	}
	*/

	return ETrait::T_None;
}

ETrait FBoardTraitMap::Remove(ETrait trait)
{
	if (m_TraitCounts.Contains(trait))
	{
		m_TraitCounts[trait] = m_TraitCounts[trait] - 1;
		UE_LOG(LogTemp, Warning, TEXT("Removed Trait: %d"), trait);
	}
	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to Remove Trait that was not found in Map: %d"), trait);
	}

	// p_Representing->SetTraitsUI();

	/*
	if (m_TraitCounts[trait] < 5)
	{
		return trait;
	}
	*/

	return ETrait::T_None;
}
