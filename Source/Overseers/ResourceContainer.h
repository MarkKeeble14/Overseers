// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResourceContainer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OVERSEERS_API UResourceContainer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResourceContainer();

	// Resource
	UPROPERTY(EditAnywhere)
	float m_MaxResource = 100;

	float m_Resource;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Mana
	UFUNCTION(BlueprintCallable)
	float GetCurrent() { return m_Resource; }

	UFUNCTION(BlueprintCallable)
	float GetMax() { return m_MaxResource; }

	UFUNCTION(BlueprintCallable)
	float GetPercent() { return m_Resource / m_MaxResource; }

	UFUNCTION(BlueprintCallable)
	bool HasEnough(float amount) { return m_Resource >= amount; }

	UFUNCTION(BlueprintCallable)
	void AlterResource(float amount);
};
