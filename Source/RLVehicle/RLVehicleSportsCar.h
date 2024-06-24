// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RLVehiclePawn.h"
#include "RLVehicleSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class RLVEHICLE_API ARLVehicleSportsCar : public ARLVehiclePawn
{
	GENERATED_BODY()
	
public:

	ARLVehicleSportsCar();
};
