// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoundType.h"
#include "GridManager.h"
#include "RoundManager.generated.h"

UCLASS()
class OVERSEERS_API ARoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Replicated)
	bool m_GameBegun;

	UPROPERTY(Replicated)
	int m_CurrentRoundNumber;

	UPROPERTY(Replicated)
	ERoundType m_CurrentRoundType;

	UPROPERTY(EditAnywhere)
	float m_PlanningRoundDuration;

	UPROPERTY(Replicated)
	float m_PlanningRoundTimer;

	UPROPERTY(Replicated)
	int m_CombatsActive;

	UPROPERTY(Replicated)
	int m_CombatSeparatorState;

	bool IsCurrentRoundCompleted(float DeltaTime);

	void NextRound();

	AGridManager* p_GridManager;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void SetGridManager(AGridManager* GridManager) { p_GridManager = GridManager; }

	UFUNCTION(BlueprintCallable)
	void CombatConcluded();

	UFUNCTION(BlueprintCallable)
	void BeginGame() { m_GameBegun = true; }

	UFUNCTION(BlueprintCallable)
	float GetPlanningRoundTimer() { return m_PlanningRoundTimer; }

	UFUNCTION(BlueprintCallable)
	ERoundType GetCurrentRoundType() { return m_CurrentRoundType; }
};
