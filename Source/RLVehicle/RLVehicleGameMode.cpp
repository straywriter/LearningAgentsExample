// Copyright Epic Games, Inc. All Rights Reserved.

#include "RLVehicleGameMode.h"
#include "RLVehiclePlayerController.h"

ARLVehicleGameMode::ARLVehicleGameMode()
{
	PlayerControllerClass = ARLVehiclePlayerController::StaticClass();
}
