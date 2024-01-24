// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerData.h"

// Sets default values for this component's properties
UPlayerData::UPlayerData()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerData::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// Get the network manager
	p_NetworkManager = Cast<AMyNetworkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMyNetworkManager::StaticClass()));

	// Get a reference to the select looking at component
	USelectLookingAt* selectLookingAt = GetOwner()->FindComponentByClass<USelectLookingAt>();

	// Set the player Index
	if (selectLookingAt != nullptr && p_NetworkManager != nullptr)
	{
		selectLookingAt->SetCanSelectBelongingTo(p_NetworkManager->GetNextPlayerIndex());
	}
}


// Called every frame
void UPlayerData::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

