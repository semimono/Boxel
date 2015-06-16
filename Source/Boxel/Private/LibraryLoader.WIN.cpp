
#ifdef _WIN32


#include "LibraryLoader.h"

#include <windows.h>

const char *LIB_EXTENSION = ".dll";


using namespace std;


void DynamicLibrary::unload() {
	if (lib == NULL) return;
	FreeLibrary((HMODULE)lib);
	lib = NULL;
}

void* DynamicLibrary::loadLibrary() {
	void* lib = LoadLibrary((libName + LIB_EXTENSION).c_str());
	if (lib == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Failed to load library: %s"), GetLastError());
	}
	return lib;
}

void* DynamicLibrary::loadFunction(const char* funcName) const {
	return (void*) GetProcAddress((HMODULE)lib, funcName);
}

const char* DynamicLibrary::getLibExtension() const {
	return LIB_EXTENSION;
}


#endif // _WIN32
