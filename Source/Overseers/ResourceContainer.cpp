// Fill out your copyright notice in the Description page of Project Settings.


#include "ResourceContainer.h"

// Sets default values for this component's properties
UResourceContainer::UResourceContainer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResourceContainer::BeginPlay()
{
	Super::BeginPlay();

	// ...
	m_Resource = m_MaxResource;
}


// Called every frame
void UResourceContainer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResourceContainer::AlterResource(float amount)
{
	if (m_Resource + amount > m_MaxResource)
	{
		m_Resource = m_MaxResource;
	}
	else if (m_Resource + amount < 0)
	{
		m_Resource = 0;
	}
	else
	{
		m_Resource += amount;
	}
}
