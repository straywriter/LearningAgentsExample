// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLVehicleSetting.h"
#include "Engine/DeveloperSettings.h"
#include "RLVehicleDeveloperSettings.generated.h"

class ULearningAgentsNeuralNetwork;
class URLVehicleAgentsInteractor;
class URLVehicleAgentsTrainer;
class ARLVehicleEnvironmentData;
class URLVehicleSetting;

/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "RLVehicle"))
class RLVEHICLE_API URLVehicleDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:

	bool IsAllSetting();

	UPROPERTY(Config, EditAnywhere, Category = "DefaultSetting")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> EncoderNeuralNetworkAsset; /** For Make Policy*/
	
	UPROPERTY(Config, EditAnywhere, Category = "DefaultSetting")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> PolicyNeuralNetworkAsset; /** For Make Policy*/

	UPROPERTY(Config, EditAnywhere, Category = "DefaultSetting")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> DecoderNeuralNetworkAsset; /** For Make Policy*/

	UPROPERTY(Config, EditAnywhere, Category = "DefaultSetting")
	TSoftObjectPtr<ULearningAgentsNeuralNetwork> CriticNeuralNetworkAsset; /** For Make Critic*/

	/** Class */

	UPROPERTY(Config, EditAnywhere, Category = "DefaultClass")
	TSubclassOf<URLVehicleSetting> VehicleSettingClss;
	
	UPROPERTY(Config, EditAnywhere, Category = "DefaultClass")
	TSubclassOf<URLVehicleAgentsInteractor> AgentInteractorClass;

	UPROPERTY(Config, EditAnywhere, Category = "DefaultClass")
	TSubclassOf<URLVehicleAgentsTrainer> AgentTrainerClass;

	UPROPERTY(Config, EditAnywhere, Category = "DefaultClass")
	TSubclassOf<ARLVehicleEnvironmentData> EnvironmentConstantDataClass;
};
