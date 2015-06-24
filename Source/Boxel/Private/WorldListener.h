#pragma once

#include "WorldModel/renderer.h"
#include "GeneratedMeshComponent.h"

#include <unordered_map>


class VoxelWorldListener : public BaseRenderer {
public:

	VoxelWorldListener();

	virtual void addObject(SceneObject *);
	virtual void removeObject(SceneObject *);
	virtual void addCamera(CameraStructure * cam);

private:
	std::unordered_map<SceneObject*, UGeneratedMeshComponent*> meshes;
};