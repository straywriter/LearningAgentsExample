// Fill out your copyright notice in the Description page of Project Settings.


#include "RLVehicleDeveloperSettings.h"

#include "RLVehicleAgentsInteractor.h"
#include "RLVehicleAgentsTrainer.h"
#include "RLVehicleEnvironmentData.h"

bool URLVehicleDeveloperSettings::IsAllSetting()
{
	if (EncoderNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		DecoderNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		PolicyNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		CriticNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		IsValid(VehicleSettingClss.Get()) &&
		IsValid(AgentInteractorClass.Get()) &&
		IsValid(AgentTrainerClass.Get()) &&
		IsValid(EnvironmentConstantDataClass.Get()))
	{
		return true;
	}

	return false;
}
