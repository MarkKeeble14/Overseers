// Fill out your copyright notice in the Description page of Project Settings.


#include "GridCell.h"

// Sets default values for this component's properties
UGridCell::UGridCell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGridCell::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UGridCell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGridCell::Select()
{
	if (p_Material == nullptr) return;
	p_Material->SetScalarParameterValue("Selected", 1);
}

void UGridCell::Deselect()
{
	if (p_Material == nullptr) return;
	p_Material->SetScalarParameterValue("Selected", 0);
}

void UGridCell::SetDefaultColor(FVector color)
{
	// Make new material
	UStaticMeshComponent* mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
	p_Material = UMaterialInstanceDynamic::Create(mesh->GetMaterial(0), NULL);
	mesh->SetMaterial(0, p_Material);
	p_Material->SetVectorParameterValue("BaseColor", color);
}

bool UGridCell::GetIsOccupied()
{
	return p_CurrentOccupant != nullptr;
}

ACellOccupant* UGridCell::GetCurrentOccupant()
{
	return p_CurrentOccupant;
}

void UGridCell::RemoveCurrentOccupant()
{
	p_CurrentOccupant = nullptr;
}

void UGridCell::SetCurrentOccupant(ACellOccupant* occupant)
{
	if (occupant == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Occupant passed to SetCurrentOccupant is nullptr"));
		p_CurrentOccupant = nullptr;
		return;
	}

	AlignOccupantToCell(occupant);
	p_CurrentOccupant = occupant;
}

void UGridCell::SwapOccupants(UGridCell* otherCell)
{
	// ?
}

void UGridCell::AlignOccupantToCell(ACellOccupant* occupant)
{
	// Make variables
	FVector location;
	FVector bounds;
	FVector alignedPos;

	// Get the actor bounds of the cell
	GetOwner()->GetActorBounds(true, location, bounds);

	// Set the spawn position to be the cellLocation plus the number of units from the center to the top of the cell
	alignedPos = location + bounds.Z / 2;

	// Get the actor bounds of the unit
	occupant->GetActorBounds(true, location, bounds);

	// Move the spawn position up by the number of units from the center of the unit to the top of the unit
	alignedPos += FVector(0, 0, bounds.Z);

	// Set the location and scale of the unit
	occupant->SetActorLocation(alignedPos);
	int actorScale = GetOwner()->GetActorScale3D().X;
	occupant->SetActorScale3D(FVector(actorScale, actorScale, actorScale));
}
