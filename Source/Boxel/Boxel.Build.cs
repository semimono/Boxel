// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class Boxel : ModuleRules
	{
		public Boxel(TargetInfo Target)
		{
			PublicIncludePaths.AddRange(
				new string[] {
					// ... add public include paths required here ...
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"Boxel/Private",
					// ... add other private include paths required here ...
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					// ... add other public dependencies that you statically link with here ...
				}
				);
				
			PrivateDependencyModuleNames.AddRange(
				new string[] {
					"Core",
					"CoreUObject",
					"Slate",
					"SlateCore",
					"EditorStyle",
					"Engine",
					"Landscape",
					"RenderCore",
					"InputCore",
					"UnrealEd",
					"PropertyEditor",
					"ImageWrapper",
					"EditorWidgets",
				}
				);

			PrivateIncludePathModuleNames.AddRange(
				new string[] {
					"MainFrame",
					"DesktopPlatform",
					"ContentBrowser",
					"AssetTools",
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[] {
					"MainFrame",
					"DesktopPlatform",
					"ImageWrapper",
				}
				);

			// KissFFT is used by the smooth tool.
			if (UEBuildConfiguration.bCompileLeanAndMeanUE == false &&
				(Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32 || Target.Platform == UnrealTargetPlatform.Mac || Target.Platform == UnrealTargetPlatform.Linux))
			{
				AddThirdPartyPrivateStaticDependencies(Target, "Kiss_FFT");
			}
			else
			{
				Definitions.Add("WITH_KISSFFT=0");
			}
		}
	}
}