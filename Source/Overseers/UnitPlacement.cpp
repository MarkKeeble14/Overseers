// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitPlacement.h"
#include "Unit.h"

// Sets default values for this component's properties
UUnitPlacement::UUnitPlacement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUnitPlacement::BeginPlay()
{
	Super::BeginPlay();

	p_SelectLookingAt = GetOwner()->GetComponentByClass<USelectLookingAt>();
}


// Called every frame
void UUnitPlacement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (p_UnitInHand != nullptr)
	{
		// Continually set the unit to the currently selected cell
		UpdateInHandUnitPlacement();
	}
}

ACellOccupant* UUnitPlacement::CreateUnit(UClass* unit)
{
	if (p_UnitInHand != nullptr) return nullptr;

	FVector spawnPos = FVector::ZeroVector;
	AActor* spawned = GetWorld()->SpawnActor(unit, &spawnPos);

	ACellOccupant* spawnedOccupant = Cast<ACellOccupant>(spawned);

	PassUnitToHand(spawnedOccupant);

	return spawnedOccupant;
}

void UUnitPlacement::PassUnitToHand(ACellOccupant* occupant)
{
	if (occupant == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to pass a null unit to hand"));
		return;
	}
	p_UnitInHand = occupant;
	p_UnitInHand->SetPlaced(false);
}

bool UUnitPlacement::ConfirmInHandUnitPlacement(UGridCell* cell)
{
	// If there is no unit in hand, no need to place unit (obviously)
	if (p_UnitInHand == nullptr) return false;

	// Make sure the cell is not already occupied
	if (cell != nullptr && cell->GetIsOccupied()) return false;

	// Set the occupant and remove it from the players hand
	cell->SetCurrentOccupant(p_UnitInHand);
	p_UnitInHand->SetPlaced(true);
	p_UnitInHand = nullptr;

	return true;
}

int UUnitPlacement::CancelInHandUnitPlacement()
{
	// If there is no unit in hand, no need to place unit (obviously)
	if (p_UnitInHand == nullptr) return 0;

	// Set the occupant and remove it from the players hand
	AUnit* unit = Cast<AUnit>(p_UnitInHand);

	if (unit == nullptr) return 0;

	int value = unit->GetData().m_Rarity;
	p_UnitInHand->Destroy();
	p_UnitInHand = nullptr;

	return value;
}

void UUnitPlacement::UpdateInHandUnitPlacement()
{
	// If there is no unit in hand, no need to update unit (obviously)
	if (p_UnitInHand == nullptr) return;

	UGridCell* cell = p_SelectLookingAt->GetSelectedGridCell();

	if (cell != nullptr)
	{
		// Simply align the unit to the cell
		cell->AlignOccupantToCell(p_UnitInHand);
	}
}

bool UUnitPlacement::TryPickupUnit(UGridCell* cell)
{
	if (p_UnitInHand != nullptr) return false;

	if (cell != nullptr && cell->GetIsOccupied())
	{
		PassUnitToHand(cell->GetCurrentOccupant());
		cell->SetCurrentOccupant(nullptr);
		return true;
	}
	return false;
}