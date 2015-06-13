// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BoxelPrivatePCH.h"
#include "BoxelEditorMode.h"
#include "BoxelEditorStyle.h"
#include <windows.h>

void* loadLibrary(const FString& fileName) {
	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("ExternalBin/Win64/")) +fileName; // Concatenate the plugins folder and the DLL file.

	void *libraryHandle = NULL;
	if (FPaths::FileExists(filePath))
	{
		libraryHandle = FGenericPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (libraryHandle == NULL) {
			UE_LOG(LogTemp, Error, TEXT("Failed to load library: %s"), *filePath);
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed to load library; non-existant file: %s"), *filePath);
	}
	return libraryHandle;
}

void closeLibrary(void* libraryHandle) {
	FGenericPlatformProcess::FreeDllHandle(libraryHandle);
}

void* lookupFunction(void* libraryHandle, const FString& funcName) {
	return FGenericPlatformProcess::GetDllExport(libraryHandle, *funcName);
}



class FBoxelModule : public IBoxelModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FBoxelModule, Boxel)



void FBoxelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FBoxelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



