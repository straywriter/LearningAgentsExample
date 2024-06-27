// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsTrainer.h"
#include "RLVehicleAgentsManager.h"
#include "RLVehicleAgentsTrainer.generated.h"

/**
 * 
 */
UCLASS()
class RLVEHICLE_API URLVehicleAgentsTrainer : public ULearningAgentsTrainer
{
	GENERATED_BODY()

public:

	virtual void Init(ARLVehicleAgentsManager* InManager);
	
	ARLVehicleAgentsManager* GetRLVehicleManager() const { return RLVehicleLearningManager; }

	UPROPERTY()
	ARLVehicleAgentsManager* RLVehicleLearningManager;

};
