// Fill out your copyright notice in the Description page of Project Settings.


#include "EngineHelpers.h"

EngineHelpers::EngineHelpers()
{
}

EngineHelpers::~EngineHelpers()
{
}

FVector EngineHelpers::GetPositionToPlaceActorAboveActor(AActor* moving, AActor* moveTo)
{
	if (moving == nullptr && moveTo != nullptr)
	{
		return moveTo->GetActorLocation();
	}
	else if (moving != nullptr && moveTo == nullptr)
	{
		return moving->GetActorLocation();
	}
	else if (moving == nullptr && moveTo == nullptr)
	{
		return FVector::ZeroVector;
	}

	// Make variables
	FVector location;
	FVector bounds;
	FVector alignedPos;

	// Get the actor bounds of the cell
	moveTo->GetActorBounds(true, location, bounds);

	// Set the spawn position to be the cellLocation plus the number of units from the center to the top of the cell
	alignedPos = location + bounds.Z / 2;

	// Get the actor bounds of the unit
	moving->GetActorBounds(true, location, bounds);

	// Move the spawn position up by the number of units from the center of the unit to the top of the unit
	alignedPos += FVector(0, 0, bounds.Z);

	// Set the location and scale of the unit
	moving->SetActorLocation(alignedPos);

	return alignedPos;
}

void EngineHelpers::AlignActorAboveActor(AActor* moving, AActor* moveTo)
{
	if (moving == nullptr || moveTo == nullptr) return;

	// Set the location and scale of the unit
	moving->SetActorLocation(GetPositionToPlaceActorAboveActor(moving, moveTo));

	// UE_LOG(LogTemp, Warning, TEXT("Setting location of %s to <%f, %f, %f> - MoveTo = %s"), *moving->GetName(), alignedPos.X, alignedPos.Y, alignedPos.Z, *moveTo->GetName());
}

template<typename T>
static void EngineHelpers::FindAllActors(UWorld* world, TArray<T*>& out)
{
	for (TActorIterator<T> It(world); It; ++It)
	{
		out.Add(*It);
	}
}