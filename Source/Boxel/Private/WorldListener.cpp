
#include "BoxelPrivatePCH.h"
#include "WorldListener.h"
#include "VoxelObject.h"

using namespace std;


VoxelWorldListener::VoxelWorldListener(AVoxelObject* master): master(master) {
}

void VoxelWorldListener::addObject(SceneObject* object) {
	UGeneratedMeshComponent* mesh = meshes[object];
	if (mesh == NULL) {
		mesh = master->CreateDefaultSubobject<UGeneratedMeshComponent>(TEXT("GeneratedMesh"), false);
		meshes[object] = mesh;
	}
	vector<Face*>& faces = object->getFaces();
	TArray<FGeneratedMeshTriangle> triangles;
	for (Face* face : faces) {
		const vector<Vector3<double> >& vertices = face->getVertices();
		FGeneratedMeshTriangle triangle;
		triangle.Vertex0 = FVector(vertices[0].x, vertices[0].y, vertices[0].z);
		triangle.Vertex1 = FVector(vertices[1].x, vertices[1].y, vertices[1].z);
		triangle.Vertex2 = FVector(vertices[2].x, vertices[2].y, vertices[2].z);
		triangles.Add(triangle);
	}
	mesh->SetGeneratedMeshTriangles(triangles);
}

void VoxelWorldListener::removeObject(SceneObject* object) {
	UGeneratedMeshComponent* mesh = meshes[object];
	meshes.erase(object);
	if (mesh == NULL)
		return;
	mesh->DestroyComponent(true);
}

void VoxelWorldListener::addCamera(CameraStructure * cam) {
	// we don't care about cameras
}
