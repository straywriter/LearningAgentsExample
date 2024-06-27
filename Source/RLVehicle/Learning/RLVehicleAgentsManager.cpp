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
	
	LearningAgentsManager = CreateDefaultSubobject<ULearningAgentsManager>(TEXT("LearningAgentsManager"));
}

// Called when the game starts or when spawned
void ARLVehicleAgentsManager::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

// Called every frame
void ARLVehicleAgentsManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
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
	*/

}

PRAGMA_DISABLE_OPTIMIZATION

void ARLVehicleAgentsManager::Init()
{
	//1. Init settings
	if(!InitSettings())
		return;

	//2. Init environment
	InitEnvironmentData();

	//3. Make Interactor
	MakeInteractor();
	if(!Interactor)
		return;
	Interactor->Init(this);

	//4. Make Policy
	MakePolicy();

	//5. Make Critic
	MakeCircle();

	//6. Make Trainer
	MakeTrainer();
	if(!Trainer)
		return;
	Trainer->Init(this);
	
}
PRAGMA_ENABLE_OPTIMIZATION

/** TODO: 如果每个训练场景中只有一个Setting, 可以放到Subsystem初始化, Project Setting设置 */
bool ARLVehicleAgentsManager::InitSettings()
{
	// Init default settings
	const auto DefaultSetting = GetMutableDefault<URLVehicleDeveloperSettings>();

	if(!DefaultSetting->IsAllSetting())
	{
		UE_LOG(LogTemp, Error, TEXT("DefaultSetting is invalid"));
	}

	// Init settings
	if(SettingAsset)
    {
		Setting = NewObject<URLVehicleSetting>(this, SettingAsset);
    }
	else
	{
		Setting = NewObject<URLVehicleSetting>(this, DefaultSetting->VehicleSettingClss);
		UE_LOG(LogTemp, Warning, TEXT("Load DefaultSetting"));
	}

	return bInitSettings = true;
}

void ARLVehicleAgentsManager::InitEnvironmentData()
{
	// TODO: 暂时场景中通过EditInstanceOnly指定
}

PRAGMA_DISABLE_OPTIMIZATION

void ARLVehicleAgentsManager::MakeInteractor()
{
	Interactor = Cast<URLVehicleAgentsInteractor>(
		ULearningAgentsInteractor::MakeInteractor(
			LearningAgentsManager,
			TSubclassOf<ULearningAgentsInteractor>(Setting->AgentInteractorClass),
			TEXT("Name")));
	
}
PRAGMA_ENABLE_OPTIMIZATION

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
			TSubclassOf<ULearningAgentsTrainer>(Setting->AgentTrainerClass)));
	
}

