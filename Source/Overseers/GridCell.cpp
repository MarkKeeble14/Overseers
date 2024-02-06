// Fill out your copyright notice in the Description page of Project Settings.

#include "GridCell.h"
#include "EngineHelpers.h"

// Sets default values for this component's properties
UGridCell::UGridCell()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
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

	p_CurrentOccupant = occupant;
	EngineHelpers::AlignActorAboveActor(p_CurrentOccupant, GetOwner());
}

void UGridCell::SwapOccupants(UGridCell* otherCell)
{
	// ?
}

void UGridCell::Clear()
{
	if (p_CurrentOccupant == nullptr) return;
	p_CurrentOccupant->Remove();
}
