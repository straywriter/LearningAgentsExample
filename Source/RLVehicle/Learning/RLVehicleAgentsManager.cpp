// Fill out your copyright notice in the Description page of Project Settings.


#include "RLVehicleAgentsManager.h"

#include "LearningAgentsInteractor.h"
#include "LearningAgentsManager.h"
#include "RLVehicleAgentsTrainer.h"
#include "Learning/RLVehicleAgentsInteractor.h"
#include "RLVehicleDeveloperSettings.h"

// Sets default values
ARLVehicleAgentsManager::ARLVehicleAgentsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARLVehicleAgentsManager::BeginPlay()
{
	Super::BeginPlay();

	LearningAgentsManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("LearningAgentsManager"));
}

// Called every frame
void ARLVehicleAgentsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bRunInference)
	{
		Policy->RunInference();
	}
	else
	{
		Trainer->RunTraining(
			Setting->AgentsTrainerTrainingSettings,
			Setting->AgentsTrainerGameSettings,
			Setting->AgentsTrainerPathSettings,
			true,
			true);
	}

}

void ARLVehicleAgentsManager::Init()
{

	//1. Init settings
	if(!InitSettings())
		return;

	//2. Init environment

	//3. Make Interactor

	//4. Make Policy

	//5. Make Critic

	//6. Make Trainer
	
}

/** TODO: 如果每个训练场景中只有一个Setting, 可以放到Subsystem初始化, Project Setting设置 */
bool ARLVehicleAgentsManager::InitSettings()
{
	// Init default settings
	const auto DefaultSetting = GetMutableDefault<URLVehicleDeveloperSettings>();

	if(!DefaultSetting->IsAllSetting())
	{
		UE_LOG(LogTemp, Fatal, TEXT("DefaultSetting is invalid"));
	}

	// Init settings
	if(SettingAsset.IsValid())
	{
		Setting = SettingAsset.LoadSynchronous();
	}
	else
	{
		Setting = DefaultSetting->VehicleSettingAsset.IsValid() ? DefaultSetting->VehicleSettingAsset.LoadSynchronous() : nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Load DefaultSetting"));
	}

	if(Setting)
	{
		bInitSettings = true;
		UE_LOG(LogTemp, Log, TEXT("Success Load Setting"));
	}

	return bInitSettings;
}

void ARLVehicleAgentsManager::InitEnvironmentData()
{
	
}

void ARLVehicleAgentsManager::MakeInteractor()
{
	Interactor = Cast<URLVehicleAgentsInteractor>(
		ULearningAgentsInteractor::MakeInteractor(
			LearningAgentsManager,
			TSubclassOf<ULearningAgentsInteractor>(Setting->AgentInteractorClass),
			TEXT("Name")));
	
}

void ARLVehicleAgentsManager::MakePolicy()
{
	Policy = ULearningAgentsPolicy::MakePolicy(
		LearningAgentsManager,
		Interactor,
		TSubclassOf<ULearningAgentsPolicy>(ULearningAgentsPolicy::StaticClass()));
	
}

void ARLVehicleAgentsManager::MakeCircle()
{
	Critic = ULearningAgentsCritic::MakeCritic(
		LearningAgentsManager,
		Interactor,
		Policy,
		TSubclassOf<ULearningAgentsCritic>(ULearningAgentsCritic::StaticClass()));
}

void ARLVehicleAgentsManager::MakeTrainer()
{
	Trainer = Cast<URLVehicleAgentsTrainer>(
		ULearningAgentsTrainer::MakeTrainer(
			LearningAgentsManager,
			Interactor,
			Policy,
			Critic,
			TSubclassOf<ULearningAgentsTrainer>(Setting->AgentInteractorClass)));
	
}

