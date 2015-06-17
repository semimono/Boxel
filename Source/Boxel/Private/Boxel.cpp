// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "BoxelPrivatePCH.h"
#include "DynamicLibrary.h"

#include "Voxel/cInterface.h"


void* loadLibrary(const FString& fileName) {
	FString filePath = FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/")) +fileName; // Concatenate the plugins folder and the DLL file.

	void *libraryHandle = NULL;
	if (FPaths::FileExists(filePath))
	{
		FString libraryDir = FPaths::GetPath(filePath);
		FPlatformProcess::PushDllDirectory(*libraryDir);
		libraryHandle = FPlatformProcess::GetDllHandle(*filePath);
		if (libraryHandle == NULL) {
			UE_LOG(LogTemp, Error, TEXT("Failed to load library: %s"), *filePath);
		}
		FPlatformProcess::PopDllDirectory(*libraryDir);
	} else {
		UE_LOG(LogTemp, Error, TEXT("Failed to load library; non-existant file: %s"), *filePath);
	}
	return libraryHandle;
}

void closeLibrary(void* libraryHandle) {
	FPlatformProcess::FreeDllHandle(libraryHandle);
}

void* lookupFunction(void* libraryHandle, const FString& funcName) {
	void* function = FPlatformProcess::GetDllExport(libraryHandle, *funcName);
	if (function == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Failed to lookup function %s"), *funcName);
		//UE_LOG(LogTemp, Error, TEXT("Failed to lookup function %s: %s"), *funcName, GetLastError());
	}
	return function;
}



class FBoxelModule : public IBoxelModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE(FBoxelModule, Boxel)


typedef void*(*_VoxMakeTree)(unsigned char maxDepth, double size);


void FBoxelModule::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	UE_LOG(LogTemp, Log, TEXT("Loading library %s"), *FString("DracoVoxel.dll"));
	void* voxelLib = loadLibrary("DracoVoxel.dll");
	UE_LOG(LogTemp, Log, TEXT("Loaded library %s"), *FString("DracoVoxel.dll"));
	_VoxMakeTree makeTree = (_VoxMakeTree) lookupFunction(loadLibrary, FString("voxMakeTree"));
	UE_LOG(LogTemp, Log, TEXT("Looked up function %s"), *FString("voxMakeTree"));

	void* tree = makeTree((unsigned char) 6, 10.0);
	UE_LOG(LogTemp, Log, TEXT("Called function %s"), *FString("voxMakeTree"));


	//UE_LOG(LogTemp, Log, TEXT("Loading library %s"), *FString("DracoVoxel.dll"));
	//DynamicLibrary lib(FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/DracoVoxel.dll")));
	////void * lib = LoadLibrary(FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/")).);
	//UE_LOG(LogTemp, Log, TEXT("Loaded library %s"), *FString("DracoVoxel.dll"));
	//_VoxMakeTree makeTree = (_VoxMakeTree)lookupFunction(loadLibrary, FString("voxMakeTree"));
	//UE_LOG(LogTemp, Log, TEXT("Looked up function %s"), *FString("voxMakeTree"));

	//void* tree = makeTree((unsigned char)6, 10.0);
	//UE_LOG(LogTemp, Log, TEXT("Called function %s"), *FString("voxMakeTree"));
}


void FBoxelModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



