// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Trait.h"
#include <PaperSprite.h>
#include "UnitInfo.generated.h"

USTRUCT(BlueprintType)
struct OVERSEERS_API FUnitInfo
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString m_Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_Rarity = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UPaperSprite* m_SpriteImage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<ETrait> m_Traits;
};