// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Selectable.h"
#include "CellOccupant.h"
#include "GridCell.generated.h"


UCLASS(BlueprintType)
class OVERSEERS_API UGridCell : public UActorComponent, public ISelectable
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGridCell();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UMaterialInstanceDynamic* p_Material;

	ACellOccupant* p_CurrentOccupant;

	int m_OwnedByPlayerId;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Select() override;

	virtual void Deselect() override;

	UFUNCTION(BlueprintCallable)
	virtual bool GetCountsTowardUnitMax() { return true; }

	void SetDefaultColor(FVector color);

	UFUNCTION(BlueprintCallable)
	bool GetIsOccupied();

	UFUNCTION(BlueprintCallable)
	ACellOccupant* GetCurrentOccupant();

	UFUNCTION(BlueprintCallable)
	void RemoveCurrentOccupant();

	UFUNCTION(BlueprintCallable)
	void SetCurrentOccupant(ACellOccupant* occupant);

	void SwapOccupants(UGridCell* otherCell);

	void AlignOccupantToCell(ACellOccupant* occupant);

	void SetOwnedByPlayerId(int playerId) { m_OwnedByPlayerId = playerId; }

	int GetOwnedByPlayerId() { return m_OwnedByPlayerId; }
};