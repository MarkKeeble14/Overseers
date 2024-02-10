// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CellOccupant.h"
#include "UnitInfo.h"
#include "Unit.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeathDelegate, int, playerId, AUnit*, unit);

/**
 * 
 */
UCLASS(BlueprintType)
class OVERSEERS_API AUnit : public ACellOccupant
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FUnitInfo data;

	UFUNCTION(BlueprintCallable)
	FUnitInfo GetData() { return data; }

	void IncrementStage();

	UFUNCTION(BlueprintCallable)
	int GetStage() { return m_Stage; }

	UFUNCTION(BlueprintCallable)
	int GetValue() { return FMath::Pow(3, (float)m_Stage - 1) * data.m_Rarity; }

	void SetScaleBasedOnStage();

	void Combine(AUnit* combineWith1, AUnit* combineWith2);

	// Functions for
	// Autoattack
	void Autoattack(AUnit* target);

	// Cast Ability
	void TakeOffensiveAct();

	void CastAbility(AUnit* target);

	void TakeDamage(float damage, int damageType); // 0 = AD, 1 = AP

	// Set Target
	void SetTarget(ACellOccupant* target) { p_Target = target; }

	UFUNCTION(BlueprintCallable)
	ACellOccupant* GetTarget() { return p_Target; }

	// Activate/Deactivate
	void Activate() { m_Active = true; }

	void Deactivate() { m_Active = false; }

	// Equipment
	// void EquipItem(FItem item);
	// void UnequipItem(FItem item);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealth() { return m_CurrentHealth; }

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() { return m_MaxHealth; }

	UFUNCTION(BlueprintCallable)
	float GetMaxResource() { return m_MaxResource; }

	UFUNCTION(BlueprintCallable)
	void AddResource(float amount) { m_CurrentResource += amount; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FOnDeathDelegate OnDeath;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	int m_Stage = 1;

	int m_MaxStage = 3;

	float m_CurrentTimeBetweenOffensiveActs = 0;

	float m_CurrentHealth = 0;

	float m_CurrentResource = 0;

	UPROPERTY(EditAnywhere)
	bool m_Active = false;

	// Movement
	UPROPERTY(EditAnywhere)
	ACellOccupant* p_Target;

	// Stats
	float m_TimeBetweenOffensiveActs = 1;

	// Health
	UPROPERTY(EditAnywhere)
	float m_MaxHealth = 100;

	// Max Resource
	UPROPERTY(EditAnywhere)
	float m_MaxResource = 100;

	UPROPERTY(EditAnywhere)
	float m_ResourceGainPerAttack = 10;

	// Attack Damage
	UPROPERTY(EditAnywhere)
	float m_AttackDamage = 10;

	// Ability Damage
	UPROPERTY(EditAnywhere)
	float m_AbilityDamage = 10;

	// Armor
	UPROPERTY(EditAnywhere)
	float m_Armor = 10;

	// Ability Resistence
	UPROPERTY(EditAnywhere)
	float m_AbilityResistance = 10;

	// Ability
	// Ability m_Ultimate;

	// Equipment
	// TArray<FItem> m_EquippedItems;
};
