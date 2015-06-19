#pragma once

#include "DynamicLibrary.h"
#include "Voxel/cInterface.h"
#include "Voxel/tree.h"
#include "Voxel/mutators/sphere.h"


class VoxelLibrary: private DynamicLibrary {
public:
	static Vox::Tree* makeTree(unsigned char depth, double size);

	static void freeTree(Vox::Tree* tree);

	static Vox::SphereMut* makeSphereMut(double x, double y, double z, double radius, double opacity, unsigned short matType);

private:
	VoxMakeTreeFunc makeTreeFunc;
	VoxEraseTreeFunc freeTreeFunc;
	VoxSphereMutatorFunc makeSphereMutFunc;

	static VoxelLibrary singleton;

	virtual bool load();
	

	static VoxelLibrary& get(); // get the singleton (no need to load the library more than once)


};
