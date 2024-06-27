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
class AEnvironmentDataBase;


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

	/** Setting */
	
	bool bInitSettings = false;

	bool InitSettings();

	URLVehicleSetting* GetSetting() { return Setting; }
	
	/** Environment Data */

	// TODO: 暂时只支持单场景多Agent训练, 后续支持多场景多Agent训练
	void InitEnvironmentData();

	AEnvironmentDataBase* GetEnvironmentData() const { return EnvironmentData; }

	UPROPERTY(EditInstanceOnly, Category="RLVehicle")
	AEnvironmentDataBase* EnvironmentData;

	/** Train */

	void MakeInteractor();
	
	void MakePolicy();
	
	void MakeCircle();
	
	void MakeTrainer();

	// TODO: 多线程优化, 
	void BeginTraning();

	UPROPERTY(EditAnywhere)
	bool bRunInference;

	UPROPERTY(VisibleAnywhere)
	URLVehicleAgentsTrainer* Trainer;

	UPROPERTY(VisibleAnywhere)
	URLVehicleAgentsInteractor* Interactor;
	
	UPROPERTY()
	ULearningAgentsPolicy* Policy;
	
	UPROPERTY()
	ULearningAgentsCritic* Critic;

	UPROPERTY(EditAnywhere)
	ULearningAgentsManager* LearningAgentsManager;

	/** Set URLVehicleSetting blueprint instance */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RLVehicle")
	TSubclassOf<URLVehicleSetting> SettingAsset;

private:

	UPROPERTY(EditAnywhere, Instanced)
	URLVehicleSetting* Setting;

	UPROPERTY()
	TArray<AActor*> AgentsActors;
	
	
};
