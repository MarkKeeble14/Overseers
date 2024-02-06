// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class OVERSEERS_API EngineHelpers
{
public:
	EngineHelpers();
	~EngineHelpers();

	template<typename T>
	static void FindAllActors(UWorld* world, TArray<T*>& out);

	static FVector GetPositionToPlaceActorAboveActor(AActor* a1, AActor* a2);

	static void AlignActorAboveActor(AActor* a1, AActor* a2);
};
