// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "MyNetworkManager.h"
#include <Kismet/GameplayStatics.h>
#include "GridManager.h"
#include "TraitsManager.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraitAddedToBoardSignature, ETrait, trait);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTraitRemovedFromBoardSignature, ETrait, trait);

UCLASS()
class OVERSEERS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	UPROPERTY(EditAnywhere)
	UInputMappingContext* myInputMappingContext;

	// Jumping
	UPROPERTY(EditAnywhere)
	float jumpStrength = 1000;

	// Gravity
	UPROPERTY(EditAnywhere)
	float defaultGravityScale = 3;

	// Oversight Movement
	UPROPERTY(EditAnywhere)
	float oversightBaseFlySpeed = 10;
	UPROPERTY(EditAnywhere)
	float oversightBoostedFlySpeed = 20;

	UPROPERTY(EditAnywhere)
	float airDashMaxBoost = 5;
	UPROPERTY(EditAnywhere)
	float airDashBoostFadeRate = 5;

	// Grounded Movement
	UPROPERTY(EditAnywhere)
	float groundedMoveSpeed = 600;
	UPROPERTY(EditAnywhere)
	float groundedSprintSpeed = 1200;

	// Mode Transitions
	UPROPERTY(EditAnywhere)
	float modeTransitionDelay = 0.5f;

	UPROPERTY(EditAnywhere)
	float m_OversightToGroundedForceMultiplier = 100;

	// Oversight
	UPROPERTY(EditAnywhere)
	float ascendSpeed = 2500;
	UPROPERTY(EditAnywhere)
	float oversightAscendTo = 4000;
	UPROPERTY(EditAnywhere)
	float m_AscendTransitionSpeedMult = 3;
	UPROPERTY(EditAnywhere)
	float m_DescendTransitionSpeedMult = 7.5;

	// References
	AGridManager* p_GridManager;

	ATraitsManager* p_TraitsManager;

	int m_PlayerId = 0;

	// Game HP
	UPROPERTY(EditAnywhere)
	float m_MaxPlayerGameHP = 100;

	float m_PlayerGameHP;

	float m_XBound;

	float m_YBound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateSpeed();
	void ResetMovementStates();

	void GroundedToOversight(float DeltaTime);
	void OversightToGrounded(float DeltaTime);

	float currentAirDashBoost;

	float modeTransitionDelayTimer;
	float currentTransitionTime;

	bool allowMovementInput = true;

	float currentOversightFlySpeed;
	float oversightDescendTo;

	bool isSprinting;
	bool isCrouched;

	int playerMode; // 0 = Grounded, 1 = Oversight, 2 = G -> O Transition. 3 -> O -> G Transition
public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool AlterGameHP(float amount);

	UFUNCTION(BlueprintCallable)
	void MoveForward(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float AxisValue);

	UFUNCTION(BlueprintCallable)
	void CallJump();

	UFUNCTION(BlueprintCallable)
	void StartSprint();

	UFUNCTION(BlueprintCallable)
	void StopSprint();

	UFUNCTION(BlueprintCallable)
	void StartCrouch();

	UFUNCTION(BlueprintCallable)
	void StopCrouch();

	UFUNCTION(BlueprintCallable)
	void ToggleMode();

	UFUNCTION(BlueprintCallable)
	bool GetIsSprinting() { return isSprinting; }

	UFUNCTION(BlueprintCallable)
	int GetPlayerMode() { return playerMode; }

	UFUNCTION(BlueprintCallable)
	void SetPlayerId(int id) { m_PlayerId = id; }

	UFUNCTION(BlueprintCallable)
	int GetPlayerId() { return m_PlayerId; }

	FBoardData* GetPlayerBoardData() { return p_GridManager->GetPlayerBoardData(m_PlayerId); }

	UFUNCTION(BlueprintCallable)
	void SetGridManager(AGridManager* gridManager) { p_GridManager = gridManager; }

	UFUNCTION(BlueprintCallable)
	void SetTraitsManager(ATraitsManager* traitsManager) { p_TraitsManager = traitsManager; }

	UPROPERTY(BlueprintAssignable)
	FOnTraitAddedToBoardSignature OnTraitAddedToBoard;

	UPROPERTY(BlueprintAssignable)
	FOnTraitRemovedFromBoardSignature OnTraitRemovedFromBoard;

	bool DidChangeTraitBreakpointRegion(ETrait trait, int previous, int current);

	void SetBounds(float x, float y) { m_XBound = x; m_YBound = y; }

	void LockToBounds(FVector& vec);
};
