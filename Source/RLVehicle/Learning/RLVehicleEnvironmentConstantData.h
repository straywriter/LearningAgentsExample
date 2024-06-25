// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RLVehicleEnvironmentConstantData.generated.h"


/**
 * Environment Constant Data, store static data in different environments, need to be initialized
 * Example : Track spline
 */
UCLASS()
class RLVEHICLE_API ARLVehicleEnvironmentConstantData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLVehicleEnvironmentConstantData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Init(){}

};
