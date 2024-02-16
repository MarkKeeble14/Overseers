// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundManager.h"
#include "CombatManager.h"
#include <Net/UnrealNetwork.h>

// Sets default values
ARoundManager::ARoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	m_CombatSeparatorState = 0;
}

// Called when the game starts or when spawned
void ARoundManager::BeginPlay()
{
	Super::BeginPlay();

	// Begin Round Loop
	m_CurrentRoundNumber = 0;
	m_CurrentRoundType = ERoundType::T_Planning;
	m_PlanningRoundTimer = m_PlanningRoundDuration;
}

void ARoundManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(ARoundManager, Owner);

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

bool ARoundManager::IsCurrentRoundCompleted(float DeltaTime)
{
	switch (m_CurrentRoundType)
	{
		case ERoundType::T_Planning:
			if (m_PlanningRoundTimer <= 0)
			{
				return true;
			}
			else
			{
				m_PlanningRoundTimer -= DeltaTime;
				return false;
			}
		case ERoundType::T_Combat:
			return m_CombatsActive <= 0;
		default:
			return false;
	}
}

// Called every frame
void ARoundManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_GameBegun) return;

	if (m_WaitingOnNextRoundDelayTimer)
	{
		m_NextRoundDelayTimer -= DeltaTime;
		if (m_NextRoundDelayTimer < 0)
		{
			p_CombatManager->Reset();

			NextRound();
			m_WaitingOnNextRoundDelayTimer = false;
		}
		return;
	}

	if (IsCurrentRoundCompleted(DeltaTime))
	{
		p_CombatManager->IncreaseDamagePerUnit();

		m_NextRoundDelayTimer = m_NextRoundDelay;
		m_WaitingOnNextRoundDelayTimer = true;
		UE_LOG(LogTemp, Warning, TEXT("Round Complete, Beginning Delay"));
	}
}

void ARoundManager::NextRound()
{
	m_CurrentRoundNumber++;
	m_CurrentRoundType = (ERoundType)(m_CurrentRoundNumber % 2);
	
	UE_LOG(LogTemp, Warning, TEXT("New Round (Round #%d)"), m_CurrentRoundNumber);

	switch (m_CurrentRoundType)
	{
		case ERoundType::T_Planning:
			m_PlanningRoundTimer = m_PlanningRoundDuration;

			p_GridManager->SetupMatches(2);
			break;
		case ERoundType::T_Combat:
			m_CombatsActive = 2;

			p_GridManager->SetupMatches(m_CombatSeparatorState);
			if (m_CombatSeparatorState == 0)
			{
				//
				p_CombatManager->SetupMatch(0, 1);
				p_CombatManager->SetupMatch(2, 3);
			}
			else
			{
				// 
				p_CombatManager->SetupMatch(0, 3);
				p_CombatManager->SetupMatch(1, 2);
			}
			m_CombatSeparatorState++;
			if (m_CombatSeparatorState > 1)
			{
				m_CombatSeparatorState = 0;
			}
			break;
		default:
			break;
	}
}

void ARoundManager::CombatConcluded()
{
	if (m_CombatsActive <= 0 || m_CurrentRoundType != ERoundType::T_Combat) return;
	m_CombatsActive -= 1;
}

