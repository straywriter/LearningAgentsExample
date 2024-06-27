// Fill out your copyright notice in the Description page of Project Settings.

#include "RLVehicleAgentsInteractorBase.h"

#include "ChaosVehicleMovementComponent.h"
#include "EnvironmentDataBase.h"
#include "Components/SplineComponent.h"
#include "Learning/RLVehicleSetting.h"

void URLVehicleAgentsInteractorBase::Init(ARLVehicleAgentsManager* InManager)
{
	Super::Init(InManager);

	auto Verify = Cast<AEnvironmentDataBase>(InManager->GetEnvironmentData());
	if (Verify == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("EnvironmentData is not EnvironmentDataBase"));
		return;
    }

	EnvironmentData = Verify;
}

void URLVehicleAgentsInteractorBase::GatherAgentObservation_Implementation(
	FLearningAgentsObservationObjectElement& OutObservationObjectElement,
	ULearningAgentsObservationObject* InObservationObject, const int32 AgentId)
{
	Super::GatherAgentObservation_Implementation(OutObservationObjectElement, InObservationObject, AgentId);

	const auto ObservationAgent = Cast<AgentClass>(Manager->GetAgent(AgentId, GetRLVehicleManager()->GetSetting()->AgentClass));

	auto ObservationLocaltion = ObservationAgent->GetActorLocation();
	auto TrackSpline = EnvironmentData->TrackSpline->SplineComponent;

	const auto DistanceAlongSpline = TrackSpline->GetDistanceAlongSplineAtLocation(ObservationLocaltion, ESplineCoordinateSpace::World);
	
	// Localtion
	auto TrackElement0 = ULearningAgentsObservations::MakeLocationAlongSplineObservation(
		InObservationObject,
		TrackSpline,
		DistanceAlongSpline,
		ObservationAgent->GetActorTransform(),
		10000.f);

	// Direction
	auto TrackElement1 = ULearningAgentsObservations::MakeDirectionAlongSplineObservation(
		InObservationObject,
		TrackSpline,
		DistanceAlongSpline,
		ObservationAgent->GetActorTransform());

	// Track observation
	TMap<FName, FLearningAgentsObservationObjectElement> TrackElementsMap;

	TrackElementsMap.Add(FName(TEXT("Location")), TrackElement0);
	TrackElementsMap.Add(FName(TEXT("Direction")), TrackElement1);

	auto TrackElement = ULearningAgentsObservations::MakeStructObservation(InObservationObject, TrackElementsMap);

	// Car observation
	auto CarElement = ULearningAgentsObservations::MakeVelocityObservation(
		InObservationObject,
		ObservationAgent->GetVelocity(),
		ObservationAgent->GetActorTransform(),
		200.f);

	TMap<FName, FLearningAgentsObservationObjectElement> ElementsMap;
	ElementsMap.Add(FName(TEXT("Track")), TrackElement);
	ElementsMap.Add(FName(TEXT("Car")), CarElement);

	// Return
	OutObservationObjectElement = ULearningAgentsObservations::MakeStructObservation(InObservationObject, ElementsMap);
}

void URLVehicleAgentsInteractorBase::SpecifyAgentAction_Implementation(
	FLearningAgentsActionSchemaElement& OutActionSchemaElement, ULearningAgentsActionSchema* InActionSchema)
{

	const auto SteeringAction = ULearningAgentsActions::SpecifyFloatAction(InActionSchema, FName(TEXT("Steering")));
	const auto ThrottleBrakeAction = ULearningAgentsActions::SpecifyFloatAction(InActionSchema, FName(TEXT("ThrottleBrake")));

	TMap<FName, FLearningAgentsActionSchemaElement> ElementsMap;
	ElementsMap.Add(FName(TEXT("Steering")), SteeringAction);
	ElementsMap.Add(FName(TEXT("ThrottleBrake")), ThrottleBrakeAction);

	OutActionSchemaElement = ULearningAgentsActions::SpecifyStructAction(InActionSchema,ElementsMap);
	
}

void URLVehicleAgentsInteractorBase::PerformAgentAction_Implementation(
	const ULearningAgentsActionObject* InActionObject, const FLearningAgentsActionObjectElement& InActionObjectElement,
	const int32 AgentId)
{
	const auto ActionAgent = Cast<AgentClass>(Manager->GetAgent(AgentId, GetRLVehicleManager()->GetSetting()->AgentClass));

	TMap<FName, FLearningAgentsActionObjectElement> Elements;
	ULearningAgentsActions::GetStructAction(Elements, InActionObject, InActionObjectElement);

	auto SteeringElement = Elements.Find(FName(TEXT("Steering")));

	float Steering = 0.f;
	ULearningAgentsActions::GetFloatAction(Steering, InActionObject, *SteeringElement, 1.f, FName(TEXT("Steering")));
	ActionAgent->GetVehicleMovementComponent()->SetSteeringInput(Steering);

	auto ThrottleBrakeElement = Elements.Find(FName(TEXT("ThrottleBrake")));
	float ThrottleBrake = 0.f;
	ULearningAgentsActions::GetFloatAction(ThrottleBrake, InActionObject, *ThrottleBrakeElement, 1.f, FName(TEXT("ThrottleBrake")));

	if(ThrottleBrake > 0.f)
    {
        ActionAgent->GetVehicleMovementComponent()->SetThrottleInput(ThrottleBrake);
		ActionAgent->GetVehicleMovementComponent()->SetBrakeInput(0.f);
    }
	else
	{
        ActionAgent->GetVehicleMovementComponent()->SetBrakeInput(-ThrottleBrake);
		ActionAgent->GetVehicleMovementComponent()->SetThrottleInput(0.f);
	}
}

void URLVehicleAgentsInteractorBase::SpecifyAgentObservation_Implementation(
	FLearningAgentsObservationSchemaElement& OutObservationSchemaElement,
	ULearningAgentsObservationSchema* InObservationSchema)
{
	// Basic Track Observations
	auto LocationElement = ULearningAgentsObservations::SpecifyLocationAlongSplineObservation(InObservationSchema);
	auto DirectionElement = ULearningAgentsObservations::SpecifyDirectionAlongSplineObservation(InObservationSchema);

	TMap<FName, FLearningAgentsObservationSchemaElement> TrackElementsMap;
	TrackElementsMap.Add(FName(TEXT("Location")), LocationElement);
	TrackElementsMap.Add(FName(TEXT("Direction")), DirectionElement);
	
	auto TrackElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, TrackElementsMap);

	// Car Observations
	float Velocity = 0.f;
	auto VelocityElement = ULearningAgentsObservations::SpecifyVelocityObservation(InObservationSchema);

	TMap<FName, FLearningAgentsObservationSchemaElement> ElementsMap;
	ElementsMap.Add(FName(TEXT("Track")), TrackElement);
	ElementsMap.Add(FName(TEXT("Car")), VelocityElement);

	OutObservationSchemaElement = ULearningAgentsObservations::SpecifyStructObservation(InObservationSchema, ElementsMap);
}
