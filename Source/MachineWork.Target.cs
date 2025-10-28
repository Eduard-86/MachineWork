// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class MachineWorkTarget : TargetRules
{
	public MachineWorkTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        //DefaultBuildSettings = BuildSettingsVersion.V2;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
        ExtraModuleNames.Add("MachineWork");
	}
}
