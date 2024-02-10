// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitPlacement.h"
#include "Unit.h"
#include <Kismet/GameplayStatics.h>
#include "EngineHelpers.h"

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

ACellOccupant* UUnitPlacement::CreateUnit(UClass* toSpawn)
{
	// Determine spawn position
	FBoardData* boardData = p_PlacingFor->GetPlayerBoardData();
	UGridCell* spawnOn = boardData->GetCellToSpawnOn();

	// Literally no cell to spawn on
	if (spawnOn == nullptr)
	{
		return nullptr;
	}

	FVector spawnPos = spawnOn->GetOwner()->GetActorLocation();

	// Spawn
	AActor* spawned = GetWorld()->SpawnActor(toSpawn, &spawnPos);

	// Tracking
	ACellOccupant* spawnedOccupant = Cast<ACellOccupant>(spawned);
	spawnOn->SetCurrentOccupant(spawnedOccupant);
	spawnedOccupant->SetBelongsTo(p_PlacingFor);
	spawnedOccupant->SetPlaced(true);

	// Alignment and Scale
	AUnit* unit = Cast<AUnit>(spawnedOccupant);
	if (unit != nullptr)
	{
		// Add unit to board
		boardData->AddUnitToBoard(unit);

		unit->SetScaleBasedOnStage();
	}
	else
	{
		spawnedOccupant->SetDefaultScale();
	}

	spawnedOccupant->Align();

	return spawnedOccupant;
}

void UUnitPlacement::PassUnitToHand(ACellOccupant* occupant)
{
	if (occupant == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to pass a null unit to hand"));
		return;
	}
	occupant->SetPlaced(false);
	p_UnitInHand = occupant;
}

bool UUnitPlacement::ConfirmInHandUnitPlacement(UGridCell* cell)
{
	// If there is no unit in hand, no need to place unit
	if (p_UnitInHand == nullptr) return false;

	if (cell == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to Confirm Unit Placement without a cell Selected"));
		return false;
	}

	// Make sure the cell is not already occupied
	if (cell->GetIsOccupied()) return false;

	// Set the occupant and remove it from the players hand
	cell->SetCurrentOccupant(p_UnitInHand);
	p_UnitInHand->SetPlaced(true);

	// Add the unit to the player board
	AUnit* unit = Cast<AUnit>(p_UnitInHand);
	if (unit != nullptr)
	{
		FBoardData* boardData = p_PlacingFor->GetPlayerBoardData();
		boardData->AddUnitToBoard(unit);
	}

	// Clear the unit in hand
	p_UnitInHand = nullptr;

	return true;
}

int UUnitPlacement::CancelInHandUnitPlacement()
{
	// If there is no unit in hand, no value is given
	if (p_UnitInHand == nullptr) return 0;

	// Determine value of unit being placed
	int value = 0;
	AUnit* unit = Cast<AUnit>(p_UnitInHand);
	if (unit != nullptr)
	{
		value = unit->GetValue();
	}

	// Destroy the unit
	p_UnitInHand->Destroy();

	// Clear the players hand
	p_UnitInHand = nullptr;

	// Return the value of the cleared unit
	return value;
}

void UUnitPlacement::UpdateInHandUnitPlacement()
{
	// If there is no unit in hand, no need to update unit position/scale
	if (p_UnitInHand == nullptr) return;

	// Get the selected cell
	UGridCell* cell = p_SelectLookingAt->GetSelectedGridCell();

	// If there is no cell selected, don't update unit position/scale
	if (cell == nullptr) return;

	// Determine if the occupant is a unit or just an occupant
	AUnit* unit = Cast<AUnit>(p_UnitInHand);
	if (unit != nullptr)
	{
		// Set the scale of the unit based on it's stage
		unit->SetScaleBasedOnStage();
	}
	else
	{
		// Set the default scale of the occupant
		p_UnitInHand->SetDefaultScale();
	}

	p_UnitInHand->Align(cell->GetOwner());
}

bool UUnitPlacement::TryPickupUnit(UGridCell* cell)
{
	// If there is already a unit in the players hand, don't allow them to pick up another
	if (p_UnitInHand != nullptr) return false;

	// If cell passed in is a nullptr, don't try to pick up a unit on it
	if (cell == nullptr) return false;

	// Cell must be occupied for player to be allowed to pick up a unit
	if (cell->GetIsOccupied())
	{
		// Pick up the unit
		PassUnitToHand(cell->GetCurrentOccupant());

		// If the occupant is a unit, remove it from the players board data
		AUnit* unit = Cast<AUnit>(p_UnitInHand);
		if (unit != nullptr)
		{
			FBoardData* boardData = p_PlacingFor->GetPlayerBoardData();
			boardData->RemoveUnitFromBoard(unit);
		}

		// Set the cell to have no occupant now that we have picked it up
		cell->SetCurrentOccupant(nullptr);

		// Successfully picked up a unit
		return true;
	}

	// Did not pick up a unit
	return false;
}

int UUnitPlacement::TrySellUnit(UGridCell* cell)
{
	// Don't allow player to cell a unit on no cell
	if (cell == nullptr) return 0;

	// Cell must be occupied for player to be allowed to sell the unit on it
	if (!cell->GetIsOccupied()) return 0;

	// Get the cell occupant
	ACellOccupant* occupant = cell->GetCurrentOccupant();

	// Determine if the occupant is a unit or just an occupant
	int value = 0;
	AUnit* unit = Cast<AUnit>(occupant);
	if (unit != nullptr)
	{
		// Remove unit from board
		FBoardData* boardData = p_PlacingFor->GetPlayerBoardData();
		boardData->RemoveUnitFromBoard(unit);

		// if the occupant is a unit, it has some value
		value = unit->GetValue();
	}

	// Destroy the occupant
	occupant->Destroy();

	// Set the cell to have no occupant now that we have sold it
	cell->SetCurrentOccupant(nullptr);

	return value;
}