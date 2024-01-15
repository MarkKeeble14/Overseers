// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->JumpZVelocity = jumpStrength;
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->GravityScale = playerMode == 0 ? defaultGravityScale : 0;
	
	switch (playerMode)
	{
	case 0: // Grounded
		break;
	case 1: // Oversight
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

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Input
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMyCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Repeat, this, &AMyCharacter::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMyCharacter::StopSprint);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Repeat, this, &AMyCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMyCharacter::StopCrouch);

	PlayerInputComponent->BindAction(TEXT("ToggleMode"), IE_Pressed, this, &AMyCharacter::ToggleMode);
}

void AMyCharacter::MoveForward(float AxisValue)
{
	if (!allowMovementInput)
		return;

	if (playerMode == 0) // Grounded
	{
		AddMovementInput(GetActorForwardVector() * AxisValue);
	}
	else if (playerMode == 1) // Oversight
	{
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * AxisValue * currentOversightFlySpeed);
	}
}

void AMyCharacter::MoveRight(float AxisValue)
{
	if (!allowMovementInput)
		return;

	if (playerMode == 0)	// Grounded
	{
		AddMovementInput(GetActorRightVector() * AxisValue);
	}
	else if (playerMode == 1) // Oversight
	{
		SetActorLocation(GetActorLocation() + GetActorRightVector() * AxisValue * currentOversightFlySpeed, 0);
	}
}

void AMyCharacter::Jump()
{
	if (!allowMovementInput || playerMode != 0)
		return;

	bPressedJump = true;
}

void AMyCharacter::StartSprint()
{
	if (!allowMovementInput)
		return;
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
		if (isCrouched)
		{
			GetCharacterMovement()->MaxWalkSpeed = crouchSpeed;
			return;
		}

		if (isSprinting)
		{
			GetCharacterMovement()->MaxWalkSpeed = groundedSprintSpeed;
			return;
		}
		
		GetCharacterMovement()->MaxWalkSpeed = groundedMoveSpeed;
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
		case 0:
			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			currentTransitionTime = 0;
			playerMode = 2;
			break;
		case 1:
			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);
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
	float transitionSpeedMult = 2 - currentTransitionTime;
	if (currentTransitionTime > 1) transitionSpeedMult = 1;

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
	}
}

void AMyCharacter::OversightToGrounded(float DeltaTime)
{
	float transitionSpeedMult = 2 - currentTransitionTime;
	if (currentTransitionTime > 1) transitionSpeedMult = 1;

	if (GetActorLocation().Z > oversightDescendTo)
	{
		SetActorLocation(GetActorLocation() - FVector(0, 0, descendSpeed * DeltaTime * transitionSpeedMult));
		currentTransitionTime += DeltaTime;
	}
	else 
	{
		playerMode = 0;
		ResetMovementStates();
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		allowMovementInput = true;
	}
}

void AMyCharacter::ResetMovementStates()
{
	isSprinting = false;
	isCrouched = false;
	UpdateSpeed();
}