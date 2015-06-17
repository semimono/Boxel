
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
	void* lib = LoadLibrary(*(libName +getLibExtension()));
	if (lib == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load library: %s"), GetLastError());
	}
	return lib;
}

void* DynamicLibrary::loadFunction(const char* funcName) const {
	return (void*) GetProcAddress((HMODULE)lib, funcName);
}

FString DynamicLibrary::getLibExtension() const {
	return FString(".dll");
}


#endif // _WIN32
