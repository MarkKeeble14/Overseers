// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GridManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class OVERSEERS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

protected:
	// This is where we will clean up, as the game is shut down
	virtual void Shutdown() override;

	virtual void Init() override;

private:
};
