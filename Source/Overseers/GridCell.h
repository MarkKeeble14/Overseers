// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Selectable.h"
#include "CellOccupant.h"
#include "GridCell.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Select() override;

	virtual void Deselect() override;

	void SetDefaultColor(FVector color);

	bool GetIsOccupied();

	ACellOccupant* GetCurrentOccupant();

	void RemoveCurrentOccupant();

	void SetCurrentOccupant(ACellOccupant* occupant);

	void SwapOccupants(UGridCell* otherCell);
};