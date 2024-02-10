// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trait.h"
#include "TraitsManager.generated.h"

UCLASS()
class OVERSEERS_API ATraitsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATraitsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TMap<ETrait, TArray<int>> m_TraitActivationBreakpoints;

	UFUNCTION(BlueprintCallable)
	int GetNextBreakpoint(ETrait trait, int current);

	int GetLastBreakpoint(ETrait trait, int current);

	UFUNCTION(BlueprintCallable)
	bool IsMaxBreakpoint(ETrait trait, int current);

	void InitializeTraitBreakpoints();
};
