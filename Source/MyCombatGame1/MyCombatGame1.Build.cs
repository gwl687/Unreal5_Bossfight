// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyCombatGame1 : ModuleRules
{
    public MyCombatGame1(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AnimGraphRuntime", "Kismet", "Niagara" });
    }
}
