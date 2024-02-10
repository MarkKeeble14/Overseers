// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatManager.generated.h"

class AUnit;
class AGridManager;
class ARoundManager;

UCLASS()
class OVERSEERS_API ACombatManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ACombatManager();

	AGridManager* p_GridManager;

	ARoundManager* p_RoundManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<int, int> m_ActiveMatches = {};

	TMap<int, TArray<AUnit*>> m_UnitsInCombat = {};

	void SetupMatch(int playerId1, int playerId2);
	
	void Reset();

	UFUNCTION()
	void RegisterUnitsForCombat(int playerId);

	UFUNCTION()
	void UnregisterUnitForCombat(int playerId, AUnit* unit);

	void DeactivateUnitsInMatch(int participatingPlayerId);

	void ActivateUnitsInMatch(int participatingPlayerId);

	UFUNCTION(BlueprintCallable)
	void SetGridManager(AGridManager* gridManager) { p_GridManager = gridManager; }

	UFUNCTION(BlueprintCallable)
	void SetRoundManager(ARoundManager* roundManager) { p_RoundManager = roundManager; }
};
