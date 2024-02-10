// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardUnitStageMapping.h"
#include "Unit.h"

FBoardUnitStageMapping::FBoardUnitStageMapping(TArray<AUnit*> units)
{
	for (auto it : units)
	{
		Add(it, it->GetStage());
	}
}

void FBoardUnitStageMapping::Add(AUnit* unit, int addTo)
{
	if (m_UnitsOfEachStage.Contains(addTo))
	{
		m_UnitsOfEachStage[addTo].Add(unit);

		// if there 3 of the same units that are the same stage, we combine
		if (m_UnitsOfEachStage[unit->GetStage()].Num() == 3 && unit->GetStage() < 3)
		{
			AUnit* u1 = m_UnitsOfEachStage[unit->GetStage()].Get(0);
			AUnit* u2 = m_UnitsOfEachStage[unit->GetStage()].Get(1);
			AUnit* u3 = m_UnitsOfEachStage[unit->GetStage()].Get(2);

			u1->Combine(u2, u3);
		}
	}
	else
	{
		m_UnitsOfEachStage.Add(addTo, FBoardUnitList({ unit }));
	}
}

void FBoardUnitStageMapping::Remove(AUnit* unit, int removeFrom)
{
	m_UnitsOfEachStage[removeFrom].Remove(unit);
}

int FBoardUnitStageMapping::GetNumberOfUnits()
{
	int i = 0;
	for (const TPair<int, FBoardUnitList>& pair : m_UnitsOfEachStage)
	{
		i += pair.Value.m_List.Num();
	}
	return i;
}
