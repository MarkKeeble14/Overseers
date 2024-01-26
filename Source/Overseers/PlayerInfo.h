// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct OVERSEERS_API FPlayerInfo
{
    GENERATED_USTRUCT_BODY()
    
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_PlayerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_CurrentXP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_XPForLevelUp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int m_CurrentGold;
};