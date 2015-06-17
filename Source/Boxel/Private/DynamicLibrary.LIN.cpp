
#include "BoxelPrivatePCH.h"

#ifdef __linux__


#include "DynamicLibrary.h"
#include <dlfcn.h>


const char *LIB_EXTENSION = ".so";


using namespace std;


void ScaleType::unload() {
	if (lib == NULL) return;
	dlclose(lib);
	lib = NULL;
}

void *ScaleType::loadLibrary() {
	cout << (Path::exeDir() +ROOT_PATH +SCALE_DIR +libName +LIB_EXTENSION) << endl;
	void * lib = dlopen((Path::exeDir() +ROOT_PATH +SCALE_DIR +libName +LIB_EXTENSION).c_str(), RTLD_LAZY);
	char * error = dlerror();
	if (error != NULL) {
		cerr << error << endl;
	}
	return lib;
}

void *ScaleType::loadFunction(const std::string &funcName) const {
	void *func = dlsym(lib, funcName.c_str());
	if (func == NULL) cerr << dlerror() << endl;
	return func;
}

const char *ScaleType::getLibExtension() const {
	return LIB_EXTENSION;
}


#endif // __linux__
