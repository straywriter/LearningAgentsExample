// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLVehicleSportsCar.h"
#include "Learning/RLVehicleAgentsTrainer.h"
#include "RLVehicleAgentsTrainerBase.generated.h"

class AEnvironmentDataBase;

/**
 * 
 */
UCLASS()
class RLVEHICLE_API URLVehicleAgentsTrainerBase : public URLVehicleAgentsTrainer
{
	GENERATED_BODY()
	
	using AgentClass = ARLVehicleSportsCar;

public:

	virtual void Init(ARLVehicleAgentsManager* InManager) override;

	virtual void GatherAgentReward_Implementation(float& OutReward, const int32 AgentId) override;

	virtual void ResetAgentEpisode_Implementation(const int32 AgentId) override;
	
	virtual void GatherAgentCompletion_Implementation(ELearningAgentsCompletion& OutCompletion, const int32 AgentId) override;
	
	UPROPERTY()
	AEnvironmentDataBase* EnvironmentData;
	
};
