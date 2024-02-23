// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trait.h"
#include "BoardTraitMap.generated.h"

class AMyPlayerController;

USTRUCT(BlueprintType)
struct OVERSEERS_API FBoardTraitMap
{
	GENERATED_USTRUCT_BODY()

private:
	AMyPlayerController* p_Representing;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<ETrait, int> m_TraitCounts;

	ETrait Add(ETrait trait);

	ETrait Remove(ETrait trait);

	void AttachPlayerController(AMyPlayerController* player) { p_Representing = player; }

	void LogState();
};