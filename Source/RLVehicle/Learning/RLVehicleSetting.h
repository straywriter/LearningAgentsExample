// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsCritic.h"
#include "LearningAgentsPolicy.h"
#include "LearningAgentsTrainer.h"
#include "GameFramework/Actor.h"
#include "RLVehicleSetting.generated.h"

class URLVehicleAgentsInteractor;
class URLVehicleAgentsTrainer;
class ARLVehicleEnvironmentConstantData;

/**
 * Different Settings through blueprint instance
 * Setting interactor trainer and manager
 */
UCLASS()
class RLVEHICLE_API URLVehicleSetting : public UObject
{
	GENERATED_BODY()

public:
	/** Class */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleClass")
	TSubclassOf<URLVehicleAgentsInteractor> AgentInteractorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleClass")
	TSubclassOf<URLVehicleAgentsTrainer> AgentTrainerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleClass")
	TSubclassOf<ARLVehicleEnvironmentConstantData> EnvironmentConstantDataClass;

	/** Setting */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsTrainerSettings AgentsTrainerSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsCriticSettings AgentsCriticSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsPolicySettings AgentsPolicySettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsTrainerPathSettings AgentsTrainerPathSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsTrainerGameSettings AgentsTrainerGameSettings;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleSetting")
	FLearningAgentsTrainerTrainingSettings AgentsTrainerTrainingSettings;

	/** Data Asset */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleDataAsset")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> EncoderNeuralNetworkAsset; /** For Make Policy*/
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleDataAsset")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> PolicyNeuralNetworkAsset; /** For Make Policy*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleDataAsset")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> DecoderNeuralNetworkAsset; /** For Make Policy*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicleDataAsset")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> CriticNeuralNetworkAsset; /** For Make Critic*/

	void LoadAndCheckDataAsset();

	void Init();
	
public:	
	// Sets default values for this actor's properties
	URLVehicleSetting();
};
