// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SplineActor.h"
#include "Learning/RLVehicleEnvironmentData.h"
#include "EnvironmentDataBase.generated.h"

/**
 * 
 */
UCLASS()
class RLVEHICLE_API AEnvironmentDataBase : public ARLVehicleEnvironmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditInstanceOnly, Category="RLVehicle")
	ASplineActor* TrackSpline;

};
