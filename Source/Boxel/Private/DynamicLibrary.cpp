
#include "BoxelPrivatePCH.h"
#include "DynamicLibrary.h"


using namespace std;


DynamicLibrary::DynamicLibrary() : libName(""), lib(NULL) {}
DynamicLibrary::DynamicLibrary(const FString& libName) : libName(libName), lib(NULL) {}

DynamicLibrary::~DynamicLibrary() {
	unload();
}

void DynamicLibrary::setLibName(const FString& libName) {
	unload();
	this->libName = libName;
}

bool DynamicLibrary::load() {
	unload();
	lib = loadLibrary();
	return loaded();
}


bool DynamicLibrary::loaded() const {
	return lib != NULL;
}
