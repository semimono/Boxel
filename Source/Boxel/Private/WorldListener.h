#pragma once

#include "WorldModel/renderer.h"


class VoxelWorldListener : public BaseRenderer {
public:

	VoxelWorldListener();

	virtual void addObject(SceneObject *);
	virtual void removeObject(SceneObject *);
	virtual void addCamera(CameraStructure * cam);

private:

};