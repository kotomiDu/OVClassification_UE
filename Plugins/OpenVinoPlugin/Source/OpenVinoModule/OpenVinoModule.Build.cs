// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class OpenVinoModule : ModuleRules
{
    public OpenVinoModule(ReadOnlyTargetRules Target) : base(Target)
    {
        Type = ModuleType.CPlusPlus;
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Start faster compile time for small projects:
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bFasterWithoutUnity = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "Projects",
                "OpenVinoWrapper",
			}
            );

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "../ThirdParty/OpenVinoWrapper/bin", "OpenVinoWrapper.lib"));
            RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "../ThirdParty/OpenVinoWrapper/bin", "OpenVinoWrapper.dll"));
        }
        else
        {
            // Platform not supported:
            throw new PlatformNotSupportedException("This platform is not supported for this project: " + Target.Platform.ToString());
        }
    }
}
