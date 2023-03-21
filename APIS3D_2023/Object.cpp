#include "Object.h"

Object::~Object()
{
	for (Mesh3D* mesh : meshes)
	{
		delete mesh;
	}

	meshes.clear();
}

void Object::setMesh(Mesh3D* mesh)
{
	meshes.push_back(mesh);
}

std::vector<Mesh3D*>& Object::getMeshes()
{
	return meshes;
}
