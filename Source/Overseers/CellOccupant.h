// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CellOccupant.generated.h"

class AMyPlayerController;
class UGridCell;

UCLASS()
class OVERSEERS_API ACellOccupant : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACellOccupant();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* p_PlacedMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* p_GhostMaterial;

	UMaterialInstanceDynamic* p_OwnedPlacedMaterial;
	UMaterialInstanceDynamic* p_OwnedGhostMaterial;

	UStaticMeshComponent* p_Mesh;

	bool m_Placed;

	AMyPlayerController* p_BelongsTo;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetPlaced(bool b);

	void SetScale(float scale);

	void SetDefaultScale();

	void Align();

	void Align(AActor* actor);

	void Remove(bool removeFromBoard);

	void SetBelongsTo(AMyPlayerController* player) { p_BelongsTo = player; }

	UGridCell* GetCellUnderneath();
private:
	FHitResult p_HitResult;
	FCollisionQueryParams p_QueryParams;
	FCollisionObjectQueryParams p_ObjectQueryParams;
};
