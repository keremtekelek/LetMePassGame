// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LetMePass : ModuleRules
{
	public LetMePass(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "DialogueSystemPlugin", "GameplayTags" });
	}
}
