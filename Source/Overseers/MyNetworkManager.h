// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyNetworkManager.generated.h"

UCLASS()
class OVERSEERS_API AMyNetworkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyNetworkManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int m_NextPlayerIndex = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetNextPlayerIndex()
	{
		return m_NextPlayerIndex;
	}

	void IncrementNextPlayerIndex();
};
