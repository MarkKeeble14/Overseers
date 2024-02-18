// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SelectLookingAt.h"
#include "Selectable.h"
#include "GridCell.h"
#include "GridManager.h"
#include "UnitPlacement.generated.h"

class AMyPlayerController;

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

	AMyPlayerController* p_PlacingFor;

	ACellOccupant* p_UnitInHand;

	USelectLookingAt* p_SelectLookingAt;

	void PassUnitToHand(ACellOccupant* occupant);

	void UpdateInHandUnitPlacement();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool ConfirmInHandUnitPlacement(UGridCell* cell);

	UFUNCTION(BlueprintCallable)
	int CancelInHandUnitPlacement();

	UFUNCTION(BlueprintCallable)
	bool TryPickupUnit(UGridCell* cell);

	UFUNCTION(BlueprintCallable)
	int TrySellUnit(UGridCell* cell);

	UFUNCTION(BlueprintCallable)
	ACellOccupant* CreateUnit(UClass* unit);

	UFUNCTION(BlueprintCallable)
	bool IsHandEmpty() { return p_UnitInHand == nullptr; }

	UFUNCTION(BlueprintCallable)
	int GetNumUnitsPlaced();

	UFUNCTION(BlueprintCallable)
	void SetPlacingFor(AMyPlayerController* player) { p_PlacingFor = player; }
};
