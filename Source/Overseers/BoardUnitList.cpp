// Fill out your copyright notice in the Description page of Project Settings.

#include "BoardUnitList.h"
#include "Unit.h"

// BoardUnitList
void FBoardUnitList::Add(AUnit* unit)
{
	m_List.Add(unit);
}

void FBoardUnitList::Remove(AUnit* unit)
{
	m_List.Remove(unit);
}