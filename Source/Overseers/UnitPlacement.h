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

	void TestSpawnTestUnit();

	void PassUnitToHand(ACellOccupant* occupant);

	void PickupUnit();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	UClass* m_TestUnit;

	void ConfirmInHandUnitPlacement();

	void UpdateInHandUnitPlacement();
};
