// Fill out your copyright notice in the Description page of Project Settings.


#include "RLVehicleSetting.h"

#include "RLVehicleAgentsInteractor.h"
#include "RLVehicleAgentsTrainer.h"
#include "RLVehicleEnvironmentData.h"

// Sets default values
URLVehicleSetting::URLVehicleSetting()
{
	PolicyName = TEXT("DefaultPolicy");
	InteractorName = TEXT("DefaultInteractor");
	CriticName = TEXT("DefaultCritic");
	TrainerName = TEXT("DefaultTrainer");
}

bool URLVehicleSetting::IsAllSetting()
{
	if (AgentClass &&
		AgentInteractorClass &&
		AgentTrainerClass &&
		EnvironmentConstantDataClass &&
		EncoderNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		PolicyNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		DecoderNeuralNetworkAsset.ToSoftObjectPath().IsValid() &&
		CriticNeuralNetworkAsset.ToSoftObjectPath().IsValid())
	{
		return true;
	}

	UE_LOG(LogTemp, Error, TEXT("Not all setting is set"));

	return false;
}
