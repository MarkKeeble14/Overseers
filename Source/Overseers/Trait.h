// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ETrait : uint8 {
    T_None          UMETA(DisplayName = "None"),
    T_Fire          UMETA(DisplayName = "Fire"),
    T_Water         UMETA(DisplayName = "Water"),
    T_Air           UMETA(DisplayName = "Air"),
    T_Earth         UMETA(DisplayName = "Earth"),
};
