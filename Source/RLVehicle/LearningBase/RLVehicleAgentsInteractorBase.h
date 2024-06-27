// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RLVehicleSportsCar.h"
#include "Learning/RLVehicleAgentsInteractor.h"
#include "RLVehicleAgentsInteractorBase.generated.h"

class AEnvironmentDataBase;

/**
 * 
 */
UCLASS()
class RLVEHICLE_API URLVehicleAgentsInteractorBase : public URLVehicleAgentsInteractor
{
	GENERATED_BODY()

	using AgentClass = ARLVehicleSportsCar;

public:
	virtual void Init(ARLVehicleAgentsManager* InManager) override;

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
	AEnvironmentDataBase* EnvironmentData;
};
