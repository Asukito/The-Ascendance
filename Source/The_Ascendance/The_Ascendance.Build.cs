// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class The_Ascendance : ModuleRules
{
	public The_Ascendance(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
