// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

// Cleanup. This acts as a quasi-destructor
void UMyGameInstance::Shutdown()
{
	// Important, if you overwrite functionality in UE4.
	// Omitting this, may cause errors (depending on the class).
	Super::Shutdown();
}

void UMyGameInstance::Init()
{
	Super::Init();
}
