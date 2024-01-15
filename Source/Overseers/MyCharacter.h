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

	// Gravity
	float defaultGravityScale = 3;

	// Jumping
	float jumpStrength = 1000;

	// Oversight
	float ascendSpeed = 2500;
	float oversightAscendTo = 4000;
	float descendSpeed = 3250;
	float oversightDescendTo = 100;

	// Movement
	float oversightBaseFlySpeed = 10;
	float oversightBoostedFlySpeed = 20;
	
	float groundedMoveSpeed = 600;
	float groundedSprintSpeed = 1200;
	float crouchSpeed = 300;

	float modeTransitionDelay = 0.5f;

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

	float modeTransitionDelayTimer;
	float currentTransitionTime;

	void UpdateSpeed();

	bool allowMovementInput = true;

	float currentOversightFlySpeed;
	bool isSprinting;
	bool isCrouched;

	void ResetMovementStates();

	int playerMode; // 0 = Grounded, 1 = Oversight, 2 = G -> O Transition. 3 -> O -> G Transition

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
