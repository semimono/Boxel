
#include "BoxelPrivatePCH.h"
#include "LibraryLoader.h"


using namespace std;


DynamicLibrary::DynamicLibrary(const FString& libName) : libName(libName), lib(NULL) {}

DynamicLibrary::~DynamicLibrary() {
	unload();
}

void DynamicLibrary::load() {
	unload();
	lib = loadLibrary();

	if (!lib)
		UE_LOG(LogTemp, Error, TEXT("Could not load shared library %s"), *FString(libName + getLibExtension()));
}


bool DynamicLibrary::loaded() const {
	return lib != NULL;
}
