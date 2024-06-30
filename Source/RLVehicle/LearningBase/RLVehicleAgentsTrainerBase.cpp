// Fill out your copyright notice in the Description page of Project Settings.


#include "RLVehicleAgentsTrainerBase.h"

#include "EnvironmentDataBase.h"
#include "LearningAgentsRewards.h"
#include "Components/SplineComponent.h"
#include "Learning/RLVehicleSetting.h"

void URLVehicleAgentsTrainerBase::Init(ARLVehicleAgentsManager* InManager)
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

void URLVehicleAgentsTrainerBase::GatherAgentReward_Implementation(float& OutReward, const int32 AgentId)
{
	const auto RewardAgent = Cast<AgentClass>(Manager->GetAgent(AgentId, GetRLVehicleManager()->GetSetting()->AgentClass));
	auto TrackSpline = EnvironmentData->TrackSpline->SplineComponent;

	auto VelocityReword = ULearningAgentsRewards::MakeRewardFromVelocityAlongSpline(
		TrackSpline,
		RewardAgent->GetActorLocation(),
		RewardAgent->GetVelocity(),
		1000.f,
		1.f,
		10.f);

	auto OffsetReword = ULearningAgentsRewards::MakeRewardOnLocationDifferenceAboveThreshold(
		RewardAgent->GetActorLocation(),
		TrackSpline->FindLocationClosestToWorldLocation(RewardAgent->GetActorLocation(), ESplineCoordinateSpace::World),
		800.f,
		-10.f);

	OutReward = VelocityReword + OffsetReword;
}

void URLVehicleAgentsTrainerBase::ResetAgentEpisode_Implementation(const int32 AgentId)
{
	const auto RewardAgent = Cast<AgentClass>(Manager->GetAgent(AgentId, GetRLVehicleManager()->GetSetting()->AgentClass));
	EnvironmentData->ResetToRandomPointOnSpline(RewardAgent, EnvironmentData->TrackSpline->SplineComponent);
}

void URLVehicleAgentsTrainerBase::GatherAgentCompletion_Implementation(
	ELearningAgentsCompletion& OutCompletion,
	const int32 AgentId)
{
	const auto RewardAgent = Cast<AgentClass>(Manager->GetAgent(AgentId, GetRLVehicleManager()->GetSetting()->AgentClass));
	auto TrackSpline = EnvironmentData->TrackSpline->SplineComponent;

	auto LocationOffset = TrackSpline->FindLocationClosestToWorldLocation(RewardAgent->GetActorLocation(), ESplineCoordinateSpace::World);
	OutCompletion = ULearningAgentsCompletions::MakeCompletionOnLocationDifferenceAboveThreshold(
		LocationOffset,
		RewardAgent->GetActorLocation(),
		800.f,
		ELearningAgentsCompletion::Termination);
}
