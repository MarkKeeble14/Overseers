// Fill out your copyright notice in the Description page of Project Settings.

#include "CellOccupant.h"
#include "Unit.h"
#include "MyPlayerController.h"
#include "GridManager.h"
#include "GridCell.h"
#include "EngineHelpers.h"

// Sets default values
ACellOccupant::ACellOccupant()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	p_HitResult = FHitResult(ForceInit);
	p_QueryParams = FCollisionQueryParams(FName(TEXT("Trace")), true, GetOwner());
	p_QueryParams.bTraceComplex = true;
	p_QueryParams.bReturnPhysicalMaterial = true;
	p_ObjectQueryParams = FCollisionObjectQueryParams(ECC_GameTraceChannel1);
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

void ACellOccupant::SetScale(float scale)
{
	// Set Scale
	SetActorScale3D(FVector(scale, scale, scale));
}

void ACellOccupant::SetDefaultScale()
{
	UGridCell* cell = GetCellUnderneath();
	if (cell == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Cell Underneath (SetDefaultScale)"));
		return;
	}
	AActor* cellActor = cell->GetOwner();

	// Set Scale
	float scale = cellActor->GetActorScale().X * 0.9;
	SetActorScale3D(FVector(scale, scale, scale));
}

void ACellOccupant::Align()
{
	UGridCell* cell = GetCellUnderneath();
	if (cell == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find Cell Underneath (Align)"));
		return;
	}
	EngineHelpers::AlignActorAboveActor(this, cell->GetOwner());
}

void ACellOccupant::Align(AActor* actor)
{
	if (actor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attempted to Align to nullptr (Align)"));
		return;
	}
	EngineHelpers::AlignActorAboveActor(this, actor);
}

UGridCell* ACellOccupant::GetCellUnderneath()
{
	FVector Start = GetActorLocation() + FVector(0, 0, 1000);
	FVector End = Start - FVector(0, 0, 100000);

	bool DidTrace = GetWorld()->LineTraceSingleByObjectType
	(
		p_HitResult,			//result
		Start,					//start
		End,					//end
		p_ObjectQueryParams,	//collision channel
		p_QueryParams
	);

	if (DidTrace)
	{
		return p_HitResult.GetActor()->GetComponentByClass<UGridCell>();
	}
	
	return nullptr;
}

void ACellOccupant::Remove(bool removeFromBoard)
{
	UGridCell* cell = GetCellUnderneath();
	if (cell == nullptr)
	{
		Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Removed Occupant not on Cell (Actor)"));
	}
	else
	{
		cell->SetCurrentOccupant(nullptr);

		if (removeFromBoard)
		{
			AUnit* unit = Cast<AUnit>(this);
			FBoardData* boardData = p_BelongsTo->GetPlayerBoardData();
			boardData->RemoveUnitFromBoard(unit);
		}

		Destroy();
	}
}
