// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BoxelPrivatePCH.h"
#include "DynamicLibrary.h"

#include "Voxel/cInterface.h"
#include "WorldListener.h"
#include <list>

using namespace std;


//General Log
DEFINE_LOG_CATEGORY(LogBoxel);

class FBoxelModule : public IBoxelModule
{
	DynamicLibrary voxelLib;
	VoxelWorldListener listener;


	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FBoxelModule, Boxel)



void FBoxelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	//UE_LOG(LogBoxel, Log, TEXT("Loading library %s"), *FString("DracoVoxel.dll"));
	voxelLib.setLibName(FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/DracoVoxel")));
	voxelLib.load();
	//UE_LOG(LogBoxel, Log, TEXT("Loaded library %s"), *FString("DracoVoxel.dll"));
	VoxMakeTreeFunc makeTree = (VoxMakeTreeFunc)voxelLib.loadFunction("voxMakeTree");
	//UE_LOG(LogBoxel, Log, TEXT("Looked up function %s"), *FString("voxMakeTree"));

	Vox::Tree* tree = makeTree((unsigned char)6, 10.0);
	//UE_LOG(LogBoxel, Log, TEXT("Called function %s"), *FString("voxMakeTree"));


	list<WorldModel*> worldModels = tree->getWorlds();
	worldModels.front()->addRenderer(listener);
}


void FBoxelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	voxelLib.unload();
}



void* loadLibrary(const FString& fileName) {
	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/")) + fileName; // Concatenate the plugins folder and the DLL file.

	void *libraryHandle = NULL;
	if (FPaths::FileExists(filePath)) {
		FString libraryDir = FPaths::GetPath(filePath);
		FPlatformProcess::PushDllDirectory(*libraryDir);
		libraryHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (libraryHandle == NULL) {
			UE_LOG(LogBoxel, Error, TEXT("Failed to load library: %s"), *filePath);
		}
		FPlatformProcess::PopDllDirectory(*libraryDir);
	} else {
		UE_LOG(LogBoxel, Error, TEXT("Failed to load library; non-existant file: %s"), *filePath);
	}
	return libraryHandle;
}

void closeLibrary(void* libraryHandle) {
	FPlatformProcess::FreeDllHandle(libraryHandle);
}

void* lookupFunction(void* libraryHandle, const FString& funcName) {
	void* function = FPlatformProcess::GetDllExport(libraryHandle, *funcName);
	if (function == NULL) {
		UE_LOG(LogBoxel, Error, TEXT("Failed to lookup function %s"), *funcName);
		//UE_LOG(LogTemp, Error, TEXT("Failed to lookup function %s: %s"), *funcName, GetLastError());
	}
	return function;
}
