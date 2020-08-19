// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Qua_Oct_Tree_ExampleEditorTarget : TargetRules
{
	public Qua_Oct_Tree_ExampleEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "Qua_Oct_Tree_Example" } );
	}
}
