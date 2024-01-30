// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("MyCharacter Begin Play"));
	GetCharacterMovement()->JumpZVelocity = jumpStrength;

	// Get a reference to the select looking at component
	p_SelectLookingAt = FindComponentByClass<USelectLookingAt>();
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->GravityScale = playerMode == 0 || playerMode == 3 ? defaultGravityScale : 0;

	switch (playerMode)
	{
		case 0: // Grounded

			p_SelectLookingAt->m_AllowSelect = false;

			break;
		case 1: // Oversight
			if (currentAirDashBoost > 0)
				currentAirDashBoost = FMath::Lerp(currentAirDashBoost, 0, DeltaTime * airDashBoostFadeRate);
			else
				currentAirDashBoost = 0;
			break;
		case 2: // Grouded -> Oversight
			if (modeTransitionDelayTimer > 0)
			{
				modeTransitionDelayTimer -= DeltaTime;
				break;
			}
			GroundedToOversight(DeltaTime);
			break;
		case 3: // Oversight -> Grounded
			if (modeTransitionDelayTimer > 0)
			{
				modeTransitionDelayTimer -= DeltaTime;
				break;
			}
			OversightToGrounded(DeltaTime);
			break;
	}
}

void AMyCharacter::MoveForward(float AxisValue)
{
	if (!allowMovementInput)
		return;

	FVector toMove;
	if (playerMode == 0) // Grounded
	{
		toMove = GetActorForwardVector() * AxisValue;
		toMove.Z = 0;

		AddMovementInput(toMove);
	}
	else if (playerMode == 1) // Oversight
	{
		toMove = GetActorLocation() + GetActorForwardVector() * AxisValue * currentOversightFlySpeed * (currentAirDashBoost + 1);
		toMove.Z = GetActorLocation().Z;
		SetActorLocation(toMove, 0);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if (!allowMovementInput)
		return;

	FVector toMove;
	if (playerMode == 0)	// Grounded
	{
		toMove = GetActorRightVector() * AxisValue;
		toMove.Z = 0;
		AddMovementInput(toMove);
	}
	else if (playerMode == 1) // Oversight
	{
		toMove = GetActorLocation() + GetActorRightVector() * AxisValue * currentOversightFlySpeed * (currentAirDashBoost + 1);
		toMove.Z = GetActorLocation().Z;
		SetActorLocation(toMove, 0);
	}
}

void AMyCharacter::CallJump()
{
	if (!allowMovementInput || playerMode != 0)
		return;

	bPressedJump = true;
}

void AMyCharacter::StartSprint()
{
	if (!allowMovementInput)
		return;

	if (!isSprinting && playerMode == 1)
		currentAirDashBoost = airDashMaxBoost;
	
	isCrouched = false;
	isSprinting = true;
	UpdateSpeed();

}

void AMyCharacter::StopSprint()
{
	isSprinting = false;
	UpdateSpeed();
}

void AMyCharacter::StartCrouch()
{
	if (!allowMovementInput || playerMode != 0)
		return;

	isSprinting = false;
	isCrouched = true;

	UpdateSpeed();
}

void AMyCharacter::StopCrouch()
{
	isCrouched = false;

	UpdateSpeed();
}

void AMyCharacter::UpdateSpeed()
{
	if (playerMode == 0)
	{
		if (isSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed = groundedSprintSpeed;
			return;
		}
		
		if (!isCrouched)
		{
			GetCharacterMovement()->MaxWalkSpeed = groundedMoveSpeed;
		}
		
	}
	else if (playerMode == 1)
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;

		if (isSprinting)
		{
			currentOversightFlySpeed = oversightBoostedFlySpeed;
			return;
		}

		currentOversightFlySpeed = oversightBaseFlySpeed;
	}
}

void AMyCharacter::ToggleMode()
{
	switch (playerMode)
	{
		case 0: // Begin Grouded -> Oversight
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);

			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			currentTransitionTime = 0;

			playerMode = 2;
			break;
		case 1: // Begin Oversight -> Grounded
			p_SelectLookingAt->m_AllowSelect = false;

			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			currentTransitionTime = 0;

			playerMode = 3;
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

void AMyCharacter::GroundedToOversight(float DeltaTime)
{
	float transitionSpeedMult = m_AscendTransitionSpeedMult - currentTransitionTime;
	if (transitionSpeedMult < 1) transitionSpeedMult = 1;

	if (GetActorLocation().Z < oversightAscendTo)
	{
		SetActorLocation(GetActorLocation() + FVector(0, 0, ascendSpeed * DeltaTime * transitionSpeedMult));
		currentTransitionTime += DeltaTime;
	}
	else 
	{
		playerMode = 1;
		ResetMovementStates();
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		allowMovementInput = true;
		p_SelectLookingAt->m_AllowSelect = true;
	}
}

void AMyCharacter::OversightToGrounded(float DeltaTime)
{
	float transitionSpeedMult = m_DescendTransitionSpeedMult - currentTransitionTime;
	if (transitionSpeedMult < 1) transitionSpeedMult = 1;
	GetCharacterMovement()->Launch(FVector(0, 0, -m_OversightToGroundedForceMultiplier * transitionSpeedMult));

	currentTransitionTime += DeltaTime;

	if (GetMovementComponent()->IsMovingOnGround())
	{
		playerMode = 0;
		ResetMovementStates();
		allowMovementInput = true;
	}
}

void AMyCharacter::ResetMovementStates()
{
	isSprinting = false;
	isCrouched = false;
	UpdateSpeed();
}