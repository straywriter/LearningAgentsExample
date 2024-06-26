// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LearningAgentsManager.h"
#include "LearningAgentsPolicy.h"
#include "RLVehicleAgentsManager.generated.h"

class URLVehicleSetting;
class URLVehicleAgentsTrainer;
class URLVehicleAgentsInteractor;
class ULearningAgentsPolicy;
class ULearningAgentsCritic;


UCLASS()
class RLVEHICLE_API ARLVehicleAgentsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARLVehicleAgentsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void Init();

	bool bInitSettings = false;

	bool InitSettings();

	URLVehicleSetting* GetSetting() { return Setting; }

	void InitEnvironmentData();

	void MakeInteractor();
	
	void MakePolicy();
	
	void MakeCircle();
	
	void MakeTrainer();

	// TODO: 支持同场景多训练环境情况

	// TODO: 多线程优化, 
	void BeginTraning();

	UPROPERTY(EditAnywhere)
	bool bRunInference;

	UPROPERTY()
	URLVehicleAgentsTrainer* Trainer;

	UPROPERTY()
	URLVehicleAgentsInteractor* Interactor;
	
	UPROPERTY()
	ULearningAgentsPolicy* Policy;
	
	UPROPERTY()
	ULearningAgentsCritic* Critic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicle")
	ULearningAgentsManager* LearningAgentsManager;

	/** Set URLVehicleSetting blueprint instance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicle")
	TSoftObjectPtr<URLVehicleSetting> SettingAsset;

private:

	TObjectPtr<URLVehicleSetting> Setting;
	
};
