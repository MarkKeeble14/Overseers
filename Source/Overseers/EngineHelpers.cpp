// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineHelpers.h"

EngineHelpers::EngineHelpers()
{
}

EngineHelpers::~EngineHelpers()
{
}

template<typename T>
static void EngineHelpers::FindAllActors(UWorld* world, TArray<T*>& out)
{
	for (TActorIterator<T> It(world); It; ++It)
	{
		out.Add(*It);
	}
}