// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Selectable.h"
#include "GridCell.h"
#include "SelectLookingAt.generated.h"


UCLASS()
class OVERSEERS_API USelectLookingAt : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USelectLookingAt();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	bool DoTrace();

	int m_CanSelectBelongingTo;

public:	
	bool m_AllowSelect;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float selectionDistance = 100000;

	UFUNCTION(BlueprintCallable)
	bool HasSomethingSelected() { return p_SelectedGridCell != nullptr; }

	UFUNCTION(BlueprintCallable)
	UGridCell* GetSelectedGridCell();

	UFUNCTION(BlueprintCallable)
	int TrySellUnitOnSelectedCell();

	UFUNCTION(BlueprintCallable)
	void SetCanSelectBelongingTo(int canSelect) { m_CanSelectBelongingTo = canSelect; }
private:
	FHitResult p_HitResult;
	FCollisionQueryParams p_QueryParams;
	FCollisionObjectQueryParams p_ObjectQueryParams;
	UGridCell* p_SelectedGridCell;
};
