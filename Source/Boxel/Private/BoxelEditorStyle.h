#pragma once

#include "ISettingsModule.h"
#include "ModuleManager.h"

class FBoxelEditorStyle {
public:

	static void Initialize();
	static void Shutdown();

	static TSharedPtr< class ISlateStyle > Get();

private:

	static FString InContent(const FString& RelativePath, const ANSICHAR* Extension);

	static TSharedPtr< class FSlateStyleSet > StyleSet;
};
