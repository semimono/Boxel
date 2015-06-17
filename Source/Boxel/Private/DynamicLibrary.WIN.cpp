
#include "BoxelPrivatePCH.h"

#ifdef _WIN32

#include "DynamicLibrary.h"
#include <windows.h>


using namespace std;


void DynamicLibrary::unload() {
	if (lib == NULL) return;
	FreeLibrary((HMODULE)lib);
	lib = NULL;
}

void* DynamicLibrary::loadLibrary() {
	
	FString libraryDir = FPaths::GetPath(libName);
	FPlatformProcess::PushDllDirectory(*libraryDir);

	void* lib = LoadLibrary(*(libName +getLibExtension()));
	if (lib == NULL)
		UE_LOG(LogBoxel, Error, TEXT("Failed to load library %s: %s"), *libName, GetLastError());

	FPlatformProcess::PopDllDirectory(*libraryDir);
	return lib;
}

void* DynamicLibrary::loadFunction(const char* funcName) const {
	void* func = GetProcAddress((HMODULE)lib, funcName);
	if (func == NULL)
		UE_LOG(LogBoxel, Error, TEXT("Failed to load function %s: %s"), funcName, GetLastError());
	return func;
}

FString DynamicLibrary::getLibExtension() const {
	return FString(".dll");
}


#endif // _WIN32
