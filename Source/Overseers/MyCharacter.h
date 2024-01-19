// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class OVERSEERS_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

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
	UPROPERTY(EditAnywhere)
	float crouchSpeed = 300;

	// Mode Transitions
	UPROPERTY(EditAnywhere)
	float modeTransitionDelay = 0.5f;

	// Oversight
	UPROPERTY(EditAnywhere)
	float ascendSpeed = 2500;
	UPROPERTY(EditAnywhere)
	float oversightAscendTo = 4000;
	UPROPERTY(EditAnywhere)
	float descendSpeed = 3250;
	UPROPERTY(EditAnywhere)
	float defaultOversightDescendTo = 500;
	UPROPERTY(EditAnywhere)
	float foundGroundOversightDescendTo = 100;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void Jump();

	void StartSprint();
	void StopSprint();

	void StartCrouch();
	void StopCrouch();

	void ToggleMode();
	void GroundedToOversight(float DeltaTime);
	void OversightToGrounded(float DeltaTime);

	float currentAirDashBoost;

	float modeTransitionDelayTimer;
	float currentTransitionTime;

	void UpdateSpeed();

	bool allowMovementInput = true;

	float currentOversightFlySpeed;
	float oversightDescendTo;
	bool isSprinting;
	bool isCrouched;

	void ResetMovementStates();

	bool SetOversightDescendTo();

	int playerMode; // 0 = Grounded, 1 = Oversight, 2 = G -> O Transition. 3 -> O -> G Transition
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
