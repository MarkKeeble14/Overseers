// Fill out your copyright notice in the Description page of Project Settings.


#include "CellOccupant.h"

// Sets default values
ACellOccupant::ACellOccupant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACellOccupant::BeginPlay()
{
	Super::BeginPlay();

	p_Mesh = GetComponentByClass<UStaticMeshComponent>();
	p_OwnedPlacedMaterial = UMaterialInstanceDynamic::Create(p_PlacedMaterial, NULL);
	p_OwnedGhostMaterial = UMaterialInstanceDynamic::Create(p_GhostMaterial, NULL);
}

// Called every frame
void ACellOccupant::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACellOccupant::SetPlaced(bool b)
{
	// null checks & getting references
	if (p_PlacedMaterial == nullptr || p_GhostMaterial == nullptr || p_Mesh == nullptr) return;

	m_Placed = b;
	if (b)
		p_Mesh->SetMaterial(0, p_OwnedPlacedMaterial);
	else
		p_Mesh->SetMaterial(0, p_OwnedGhostMaterial);
}
