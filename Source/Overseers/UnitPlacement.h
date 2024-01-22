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

	void CreateUnit(UClass* unit);

	void PassUnitToHand(ACellOccupant* occupant);

	void UpdateInHandUnitPlacement();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	UClass* m_TestUnit1;

	UPROPERTY(EditAnywhere)
	UClass* m_TestUnit2;

	UPROPERTY(EditAnywhere)
	UClass* m_TestUnit3;

	UFUNCTION(BlueprintCallable)
	void ConfirmInHandUnitPlacement();

	UFUNCTION(BlueprintCallable)
	void PickupUnit();

	// REMOVE
	UFUNCTION(BlueprintCallable)
	void TestSpawnTestUnit1();

	UFUNCTION(BlueprintCallable)
	void TestSpawnTestUnit2();

	UFUNCTION(BlueprintCallable)
	void TestSpawnTestUnit3();
};
