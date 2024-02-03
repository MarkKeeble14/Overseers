// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct OVERSEERS_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_PlayerLevel = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_CurrentXP = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_XPForLevelUp = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_CurrentGold = 0;
};