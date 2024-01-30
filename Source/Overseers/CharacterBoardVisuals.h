// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CharacterBoardVisuals.generated.h"

USTRUCT(BlueprintType)
struct OVERSEERS_API FCharacterBoardVisuals
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	FVector m_Color1;

	UPROPERTY(EditAnywhere)
	FVector m_Color2;
};