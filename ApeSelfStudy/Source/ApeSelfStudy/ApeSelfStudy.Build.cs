// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ApeSelfStudy : ModuleRules
{
	public ApeSelfStudy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
