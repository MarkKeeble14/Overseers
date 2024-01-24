// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Kismet/GameplayStatics.h>
#include "SelectLookingAt.h"
#include "MyNetworkManager.h"
#include "PlayerData.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERSEERS_API UPlayerData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ClassToFind;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> FoundActors;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AMyNetworkManager* p_NetworkManager;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
