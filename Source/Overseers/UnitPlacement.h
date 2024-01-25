// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectLookingAt.h"
#include "Selectable.h"
#include "GridCell.h"
#include "UnitPlacement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERSEERS_API UUnitPlacement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUnitPlacement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	ACellOccupant* p_UnitInHand;

	USelectLookingAt* p_SelectLookingAt;

	void PassUnitToHand(ACellOccupant* occupant);

	void UpdateInHandUnitPlacement();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ConfirmInHandUnitPlacement();

	UFUNCTION(BlueprintCallable)
	void PickupUnit();

	UFUNCTION(BlueprintCallable)
	void CreateUnit(UClass* unit);

	UFUNCTION(BlueprintCallable)
	bool IsHandEmpty() { return p_UnitInHand == nullptr; }
};
