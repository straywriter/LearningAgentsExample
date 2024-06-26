// Fill out your copyright notice in the Description page of Project Settings.


#include "RLVehicleDeveloperSettings.h"

#include "RLVehicleAgentsInteractor.h"
#include "RLVehicleAgentsTrainer.h"
#include "RLVehicleEnvironmentData.h"

bool URLVehicleDeveloperSettings::IsAllSetting()
{
	if (EncoderNeuralNetworkAsset.IsValid() &&
		DecoderNeuralNetworkAsset.IsValid() &&
		PolicyNeuralNetworkAsset.IsValid() &&
		CriticNeuralNetworkAsset.IsValid() &&
		VehicleSettingAsset.IsValid() &&
		IsValid(AgentInteractorClass.Get()) &&
		IsValid(AgentTrainerClass.Get()) &&
		IsValid(EnvironmentConstantDataClass.Get()))
	{
		return true;
	}

	return false;
}
