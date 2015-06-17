// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BoxelEditorPrivatePCH.h"
#include "BoxelEditorMode.h"
#include "BoxelEditorStyle.h"


//General Log
DEFINE_LOG_CATEGORY(LogBoxelEditor);


class FBoxelEditorModule : public IBoxelEditorModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FBoxelEditorModule, BoxelEditor)



void FBoxelEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	
	// register the editor mode
	FBoxelEditorStyle::Initialize();
	FEditorModeRegistry::Get().RegisterMode<FBoxelEditorMode>(
		FBoxelEditorMode::modeId,
		FText::FromName(FName("Boxel")),
		//FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.LandscapeMode", "LevelEditor.LandscapeMode.Small"),
		FSlateIcon(FBoxelEditorStyle::Get()->GetStyleSetName(), "LevelEditor.BoxelMode", "LevelEditor.BoxelMode.Small"),
		true,
		707
	);
}


void FBoxelEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



