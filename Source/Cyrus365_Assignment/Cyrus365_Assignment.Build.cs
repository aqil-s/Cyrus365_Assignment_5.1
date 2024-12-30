// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cyrus365_Assignment : ModuleRules
{
	public Cyrus365_Assignment(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "HTTP", "Json", "JsonUtilities", "UMG" });
	}
}
