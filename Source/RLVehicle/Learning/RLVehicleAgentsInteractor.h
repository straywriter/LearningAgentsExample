// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LearningAgentsInteractor.h"
#include "RLVehicleAgentsManager.h"
#include "RLVehicleAgentsInteractor.generated.h"

/**
 * 
 */
UCLASS()
class RLVEHICLE_API URLVehicleAgentsInteractor : public ULearningAgentsInteractor
{
	GENERATED_BODY()

public:

	virtual void Init(ARLVehicleAgentsManager* InManager);

	ARLVehicleAgentsManager* GetRLVehicleManager() const { return RLVehicleLearningManager; }

	virtual void GatherAgentObservation_Implementation(
	FLearningAgentsObservationObjectElement& OutObservationObjectElement,
	ULearningAgentsObservationObject* InObservationObject, const int32 AgentId) override;

	virtual void SpecifyAgentAction_Implementation(FLearningAgentsActionSchemaElement& OutActionSchemaElement,
												   ULearningAgentsActionSchema* InActionSchema) override;


	virtual void PerformAgentAction_Implementation(const ULearningAgentsActionObject* InActionObject,
												   const FLearningAgentsActionObjectElement& InActionObjectElement,
												   const int32 AgentId) override;

	virtual void SpecifyAgentObservation_Implementation(
		FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
		ULearningAgentsObservationSchema* InObservationSchema) override;
	

	UPROPERTY()
	ARLVehicleAgentsManager* RLVehicleLearningManager;

};
