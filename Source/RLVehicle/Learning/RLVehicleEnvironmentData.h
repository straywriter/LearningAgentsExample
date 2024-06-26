// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLVehicleEnvironmentData.generated.h"


/**
 * Environment Constant Data, store static data in different environments, need to be initialized
 * Example : Track spline
 */
UCLASS()
class RLVEHICLE_API ARLVehicleEnvironmentData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLVehicleEnvironmentData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Init(){}

};
