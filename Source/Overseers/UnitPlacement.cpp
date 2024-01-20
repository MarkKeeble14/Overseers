// Fill out your copyright notice in the Description page of Project Settings.

#include "UnitPlacement.h"

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

	// Bind Input
	GetOwner()->InputComponent->BindAction(TEXT("Test1"), IE_Pressed, this, &UUnitPlacement::TestSpawnTestUnit);
	GetOwner()->InputComponent->BindAction(TEXT("Test2"), IE_Pressed, this, &UUnitPlacement::ConfirmInHandUnitPlacement);
	GetOwner()->InputComponent->BindAction(TEXT("Test3"), IE_Pressed, this, &UUnitPlacement::PickupUnit);
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

void UUnitPlacement::PickupUnit()
{
	if (p_UnitInHand != nullptr) return;

	ISelectable* selected = p_SelectLookingAt->GetSelected();
	UGridCell* cell = Cast<UGridCell>(selected);

	if (cell != nullptr && cell->GetIsOccupied())
	{
		p_UnitInHand = cell->GetCurrentOccupant();
		cell->SetCurrentOccupant(nullptr);
	}
}

void UUnitPlacement::TestSpawnTestUnit()
{
	if (p_UnitInHand != nullptr) return;

	FVector spawnPos = FVector::ZeroVector;
	AActor* spawned = GetWorld()->SpawnActor(m_TestUnit, &spawnPos);

	ACellOccupant* spawnedOccupant = Cast<ACellOccupant>(spawned);

	if (spawnedOccupant != nullptr)
	{
		PassUnitToHand(spawnedOccupant);
	}
}

void UUnitPlacement::PassUnitToHand(ACellOccupant* occupant)
{
	p_UnitInHand = occupant;
}

void UUnitPlacement::ConfirmInHandUnitPlacement()
{
	p_UnitInHand = nullptr;
}

void UUnitPlacement::UpdateInHandUnitPlacement()
{
	if (p_UnitInHand == nullptr) return;

	ISelectable* selected = p_SelectLookingAt->GetSelected();
	UGridCell* cell = Cast<UGridCell>(selected);

	if (cell != nullptr && !cell->GetIsOccupied())
	{
		cell->SetCurrentOccupant(p_UnitInHand);
	}
}

