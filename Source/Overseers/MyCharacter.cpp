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

	if (!m_HasRecievedPlayerIndex)
	{
		UE_LOG(LogTemp, Warning, TEXT("MyCharacter Begin Play"));
		
		GetCharacterMovement()->JumpZVelocity = jumpStrength;

		// Get the network manager
		p_NetworkManager = Cast<AMyNetworkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyNetworkManager::StaticClass()));

		// Get a reference to the select looking at component
		p_SelectLookingAt = FindComponentByClass<USelectLookingAt>();

		// Set the player Index
		if (p_SelectLookingAt != nullptr && p_NetworkManager != nullptr)
		{
			p_SelectLookingAt->SetCanSelectBelongingTo(p_NetworkManager->GetNextPlayerIndex());
			p_NetworkManager->IncrementNextPlayerIndex();
		}

		m_HasRecievedPlayerIndex = true;
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->GravityScale = playerMode == 0 ? defaultGravityScale : 0;

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

bool AMyCharacter::SetOversightDescendTo()
{
	FVector start = GetActorLocation();
	FVector end = start - GetActorUpVector() * oversightAscendTo * 2;
	FHitResult p_HitResult = FHitResult(ForceInit);
	FCollisionQueryParams p_QueryParams = FCollisionQueryParams(FName(TEXT("Trace")), true, GetOwner());
	p_QueryParams.bTraceComplex = true;
	p_QueryParams.bReturnPhysicalMaterial = true;
	FCollisionObjectQueryParams p_ObjectQueryParams = FCollisionObjectQueryParams(ECC_GameTraceChannel1);

	bool DidTrace = GetWorld()->LineTraceSingleByObjectType(
		p_HitResult,		//result
		start,		//start
		end,		//end
		p_ObjectQueryParams,	//collision channel
		p_QueryParams
	);

	if (DidTrace)
	{
		UE_LOG(LogTemp, Warning, TEXT("Did Trace"));
		oversightDescendTo = start.Z - p_HitResult.Distance + foundGroundOversightDescendTo;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Did Not Trace"));
		oversightDescendTo = defaultOversightDescendTo;
	}

	return DidTrace;
}

void AMyCharacter::ToggleMode()
{
	switch (playerMode)
	{
		case 0: // Begin Grouded -> Oversight
			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			currentTransitionTime = 0;
			playerMode = 2;
			break;
		case 1: // Begin Oversight -> Grounded
			allowMovementInput = false;
			modeTransitionDelayTimer = modeTransitionDelay;
			GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			currentTransitionTime = 0;
			
			// Determine where to stop
			SetOversightDescendTo();

			p_SelectLookingAt->m_AllowSelect = false;

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
		p_SelectLookingAt->m_AllowSelect = true;
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