
#include "BoxelPrivatePCH.h"
#include "VoxelLibrary.h"

using namespace std;
using namespace Vox;


FString libraryName(FPaths::Combine(*FPaths::GamePluginsDir(), TEXT("Boxel/ExternalBin/Win64/DracoVoxel")));
VoxelLibrary VoxelLibrary::singleton;

VoxelLibrary& VoxelLibrary::get() {
	if (!singleton.loaded()) {
		singleton.setLibName(libraryName);
		if (!singleton.load()) {
			UE_LOG(LogBoxel, Fatal, TEXT("Failed to load voxel library, a required library for Boxel."));
		}
	}
	return singleton;
}


Tree* VoxelLibrary::makeTree(unsigned char depth, double size) {
	return get().makeTreeFunc(depth, size);
}
void VoxelLibrary::freeTree(Vox::Tree* tree) {
	get().freeTreeFunc(tree);
}
SphereMut* VoxelLibrary::makeSphereMut(double x, double y, double z, double radius, double opacity, unsigned short matType) {
	return get().makeSphereMutFunc(x, y, z, radius, opacity, matType);
}


bool VoxelLibrary::load() {
	bool succeeded = DynamicLibrary::load();
	makeTreeFunc = (VoxMakeTreeFunc) loadFunction("voxMakeTree");
	freeTreeFunc = (VoxEraseTreeFunc) loadFunction("voxEraseTree");
	makeSphereMutFunc = (VoxSphereMutatorFunc) loadFunction("voxSphereMutator");
	return succeeded &&
		makeTreeFunc != NULL &&
		freeTreeFunc != NULL &&
		makeSphereMutFunc != NULL;
}



