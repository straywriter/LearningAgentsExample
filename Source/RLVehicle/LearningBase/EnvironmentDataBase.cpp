// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvironmentDataBase.h"

#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnvironmentDataBase::ResetToRandomPointOnSpline(ARLVehicleSportsCar* Vehicle, USplineComponent* Spline)
{

	FTransform CandidateTransform;
	bool InvalidTransform = true;
	
	while (InvalidTransform)
	{
		InvalidTransform = false;

		FVector RandomPosition = FVector::ZeroVector;

		RandomPosition.X = (FMath::FRand() - 0.5f) * 1200.f;
		RandomPosition.Y = (FMath::FRand() - 0.5f) * 1200.f;
		RandomPosition.Z = 50.f;

		auto Distance = Spline->GetSplineLength() * FMath::FRand();
		FVector Position = Spline->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World) + RandomPosition;

		float RotaionZ = Spline->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World).Yaw + ((FMath::FRand() - 0.5f) * 90);

		FTransform Transform(FRotator(0, RotaionZ, 0), Position);

		if (!InvalidTransform)
		{
			if (FVector::Distance(Transform.GetLocation(), Vehicle->GetActorLocation()) < 1500)
			{
				InvalidTransform = true;
			}
		}
		
		CandidateTransform = Transform;
	}

	Vehicle->SetActorTransform(CandidateTransform, false, nullptr, ETeleportType::TeleportPhysics);
	Vehicle->GetMesh()->SetAllPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	Vehicle->GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
}
