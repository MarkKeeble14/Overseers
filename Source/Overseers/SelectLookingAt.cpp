// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectLookingAt.h"
#include "Unit.h"
#include "MyPlayerController.h"

// Sets default values for this component's properties
USelectLookingAt::USelectLookingAt()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USelectLookingAt::BeginPlay()
{
	Super::BeginPlay();

	p_HitResult = FHitResult(ForceInit);
	p_QueryParams = FCollisionQueryParams(FName(TEXT("Trace")), true, GetOwner());
	p_QueryParams.bTraceComplex = true;
	p_QueryParams.bReturnPhysicalMaterial = true;
	p_ObjectQueryParams = FCollisionObjectQueryParams(ECC_GameTraceChannel1);

	// ...

}


// Called every frame
void USelectLookingAt::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if (m_AllowSelect)
	{
		DoTrace();
	}
	else
	{
		if (p_SelectedGridCell != nullptr)
			p_SelectedGridCell->Deselect();
		p_SelectedGridCell = nullptr;
	}
}

bool USelectLookingAt::DoTrace()
{
	// Get the camera transform
	FVector CameraLoc;
	FRotator CameraRot;
	GetOwner()->GetActorEyesViewPoint(CameraLoc, CameraRot);

	FVector Start = CameraLoc;
	FVector End = CameraLoc + (CameraRot.Vector() * selectionDistance);

	bool DidTrace = GetWorld()->LineTraceSingleByObjectType(
		p_HitResult,		//result
		Start,		//start
		End,		//end
		p_ObjectQueryParams,	//collision channel
		p_QueryParams
	);

	if (DidTrace)
	{
		TSet<UActorComponent*> set = p_HitResult.GetActor()->GetComponents();
		ISelectable* selectable = nullptr;
		for (UActorComponent* c : set)
		{
			selectable = Cast<ISelectable>(c);
			if (selectable != nullptr)
				break;
		}

		UGridCell* gridCell = Cast<UGridCell>(selectable);
		if (gridCell == nullptr)
		{
			if (p_SelectedGridCell != nullptr)
				p_SelectedGridCell->Deselect();
			p_SelectedGridCell = nullptr;
		}
		else if (gridCell->GetOwnedByPlayerId() == m_SelectingFor->GetPlayerId())
		{
			if (p_SelectedGridCell != nullptr)
				p_SelectedGridCell->Deselect();
			p_SelectedGridCell = gridCell;
			p_SelectedGridCell->Select();
		}
		else 
		{
			if (p_SelectedGridCell != nullptr)
				p_SelectedGridCell->Deselect();
			p_SelectedGridCell = nullptr;
		}
	}
	else 
	{
		if (p_SelectedGridCell != nullptr)
			p_SelectedGridCell->Deselect();
		p_SelectedGridCell = nullptr;
	}

	return DidTrace;
}

UGridCell* USelectLookingAt::GetSelectedGridCell()
{
	return p_SelectedGridCell;
}
