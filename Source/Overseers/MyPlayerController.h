// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraitAddedToBoardSignature, ETrait, trait);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraitRemovedFromBoardSignature, ETrait, trait);

struct FBoardData;
class AGridManager;
class ATraitsManager;

/**
 * 
 */
UCLASS()
class OVERSEERS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	// Game HP
	UPROPERTY(EditAnywhere)
	float m_MaxPlayerGameHP = 100;

	float m_PlayerGameHP;

	int m_PlayerId = 0;

	// References
	UPROPERTY(EditAnywhere)
	AGridManager* p_GridManager;

	UPROPERTY(EditAnywhere)
	ATraitsManager* p_TraitsManager;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	bool AlterGameHP(float amount);

	FBoardData* GetPlayerBoardData();

	UPROPERTY(BlueprintAssignable)
	FOnTraitAddedToBoardSignature OnTraitAddedToBoard;

	UPROPERTY(BlueprintAssignable)
	FOnTraitRemovedFromBoardSignature OnTraitRemovedFromBoard;

	bool DidChangeTraitBreakpointRegion(ETrait trait, int previous, int current);

	UFUNCTION(BlueprintCallable)
	void SetPlayerId(int id) { m_PlayerId = id; }

	UFUNCTION(BlueprintCallable)
	int GetPlayerId() { return m_PlayerId; }

	UFUNCTION(BlueprintCallable)
	void SetGridManager(AGridManager* gridManager) { p_GridManager = gridManager; }

	UFUNCTION(BlueprintCallable)
	void SetTraitsManager(ATraitsManager* traitsManager) { p_TraitsManager = traitsManager; }
};
