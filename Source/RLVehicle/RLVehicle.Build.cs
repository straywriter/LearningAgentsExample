// Copyright Epic Games, Inc. All Rights Reserved.

using EpicGames.Core;
using UnrealBuildTool;

public class RLVehicle : ModuleRules
{
	public RLVehicle(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string []
		{
			ModuleDirectory
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput", 
			"ChaosVehicles", 
			"PhysicsCore",
			"DeveloperSettings"
		});
		
		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"LearningAgents"
		});
	}
}
