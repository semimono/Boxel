
#include "BoxelPrivatePCH.h"

#ifdef __APPLE__


#include "scaleManager.h"

#include <dlfcn.h>


const char *LIB_EXTENSION = ".dylib";


using namespace std;


void ScaleType::unload() {
	if (lib == NULL) return;
	dlclose(lib);
	lib = NULL;
}

void *ScaleType::loadLibrary() {
	return dlopen((libName +LIB_EXTENSION).c_str(), RTLD_LAZY);
}

void *ScaleType::loadFunction(const std::string &funcName) const {
	return dlsym(lib, funcName.c_str());
}

const char *ScaleType::getLibExtension() const {
	return LIB_EXTENSION;
}


#endif // __APPLE__