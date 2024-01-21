// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectLookingAt.h"

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
	DoTrace();
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

		// For some reason hit an object that is not selectable
		if (selectable == nullptr)
		{
			if (p_Selected != nullptr)
				p_Selected->Deselect();
			return false;
		}
		else // Something was hit to select
		{
			// Nothing previously selected
			if (p_Selected == nullptr)
			{
				SetSelected(selectable);
				p_Selected->Select();
			}
			else if (selectable != p_Selected) // Something different was previously selected
			{
				p_Selected->Deselect();
				SetSelected(selectable);
				p_Selected->Select();
			}
		}
	}
	else 
	{
		if (p_Selected != nullptr) p_Selected->Deselect();
		p_Selected = nullptr;
	}

	return DidTrace;
}

void USelectLookingAt::SetSelected(ISelectable* selectable)
{
	if (selectable == nullptr)
	{
		p_Selected = nullptr;
		p_SelectedGridCell = nullptr;
	}
	else
	{
		p_Selected = selectable;

		//
		UGridCell* ifGridCell = Cast<UGridCell>(p_Selected);
		if (ifGridCell != nullptr)
			p_SelectedGridCell = ifGridCell;
	}
}

ISelectable* USelectLookingAt::GetSelected()
{
	return p_Selected;
}

UGridCell* USelectLookingAt::GetSelectedGridCell()
{
	return p_SelectedGridCell;
}