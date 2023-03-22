#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Mesh3D.h"
#include <memory>

class MSH
{
public:
	const std::vector<Mesh3D::ptr>& getMeshes() { return meshes; }
	void addMesh(Mesh3D::ptr mesh) { meshes.push_back(mesh); }
private:
	std::vector<Mesh3D::ptr> meshes;
};

