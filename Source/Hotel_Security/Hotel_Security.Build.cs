// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Hotel_Security : ModuleRules
{
	public Hotel_Security(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
            "AIModule",
			"GameplayTasks",
			"GameplayTags",
            "GameplayAbilities",
            "MovieScene",
			"LevelSequence",
			"NavigationSystem",
			"UMG",
			"Niagara",
            "AdvancedWidgets"
        });
        PrivateIncludePaths.Add("HotelSecurity");
		PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
    }
}