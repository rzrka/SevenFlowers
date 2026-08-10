// Copyright QueueBitGames

using UnrealBuildTool;
using System.Collections.Generic;

public class SevenFlowerTarget : TargetRules
{
	public SevenFlowerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_7;
		DefaultBuildSettings = BuildSettingsVersion.V6;

		ExtraModuleNames.AddRange( new string[] { "SevenFlower" } );
	}
}
