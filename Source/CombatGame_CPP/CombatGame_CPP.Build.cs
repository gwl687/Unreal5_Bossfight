// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CombatGame_CPP : ModuleRules
{
    public CombatGame_CPP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "NavigationSystem", "AIModule", "Kismet", "AnimGraphRuntime", "UMG", "Slate", "SlateCore" });

    }
}
