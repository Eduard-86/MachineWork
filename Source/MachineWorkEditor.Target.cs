// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MachineWorkEditorTarget : TargetRules
{
	public MachineWorkEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		//DefaultBuildSettings = BuildSettingsVersion.V2;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("MachineWork");
        //BuildEnvironment = TargetBuildEnvironment.Unique;
        //bOverrideBuildEnvironment = true
    }
}
