// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLVehicleWheelFront.h"
#include "UObject/ConstructorHelpers.h"

URLVehicleWheelFront::URLVehicleWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}