// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLVehicleWheelRear.h"
#include "UObject/ConstructorHelpers.h"

URLVehicleWheelRear::URLVehicleWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}