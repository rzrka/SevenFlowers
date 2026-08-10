// Copyright QueueBitGames

using UnrealBuildTool;
using System.Collections.Generic;

public class SevenFlowerEditorTarget : TargetRules
{
	public SevenFlowerEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "SevenFlower" } );
	}
}
