// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BoxelPrivatePCH.h"
#include "BoxelEditorStyle.h"
#include "SlateStyle.h"

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( FBoxelEditorStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
//#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( FBoxelEditorStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
//#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( FBoxelEditorStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
//#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( FBoxelEditorStyle::InContent( RelativePath, ".ttf" ), __VA_ARGS__ )
//#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( FBoxelEditorStyle::InContent( RelativePath, ".otf" ), __VA_ARGS__ )

FString FBoxelEditorStyle::InContent(const FString& RelativePath, const ANSICHAR* Extension)
{
	static FString ContentDir = FPaths::EnginePluginsDir() / TEXT("Boxel/Content");
	return (ContentDir / RelativePath) + Extension;
}

TSharedPtr< FSlateStyleSet > FBoxelEditorStyle::StyleSet = NULL;
TSharedPtr< class ISlateStyle > FBoxelEditorStyle::Get() { return StyleSet; }

void FBoxelEditorStyle::Initialize()
{
	// Const icon sizes
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable<FSlateStyleSet>(new FSlateStyleSet("BoxelStyle"));

	// Style
	{
		//StyleSet->Set("LevelEditor.BoxelMode", new FSlateImageBrush(FPluginStyle::InContent("icon_Mode_Boxel_selected_40x", ".png"), Icon40x40));
		StyleSet->Set("LevelEditor.BoxelMode", new IMAGE_BRUSH("icon_Mode_Boxel_selected_40x", Icon40x40));
		StyleSet->Set("LevelEditor.BoxelMode.Small", new IMAGE_BRUSH("icon_Mode_Boxel_selected_40x", Icon40x40));
	}

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
};

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT

void FBoxelEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}