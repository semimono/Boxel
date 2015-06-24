#pragma once

#include "WorldModel/renderer.h"
#include "GeneratedMeshComponent.h"

#include <unordered_map>


class AVoxelObject;

class VoxelWorldListener : public BaseRenderer {
public:

	VoxelWorldListener(AVoxelObject* master);

	virtual void addObject(SceneObject *);
	virtual void removeObject(SceneObject *);
	virtual void addCamera(CameraStructure * cam);

private:
	AVoxelObject* master;
	std::unordered_map<SceneObject*, UGeneratedMeshComponent*> meshes;
};
