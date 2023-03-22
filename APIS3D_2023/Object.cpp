#include "Object.h"

void Object::setMesh(Mesh3D::ptr mesh)
{
	meshes.push_back(mesh);
}

std::vector<Mesh3D::ptr>& Object::getMeshes()
{
	return meshes;
}

