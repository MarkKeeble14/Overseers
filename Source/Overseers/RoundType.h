// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"

/**
 *
 */
UENUM(BlueprintType)
enum class ERoundType : uint8 {
    T_Planning         UMETA(DisplayName = "Planning"),
    T_Combat          UMETA(DisplayName = "Combat"),
};
