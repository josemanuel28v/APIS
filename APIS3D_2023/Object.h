#pragma once
#include "Entity.h"
#include "Mesh3D.h"
#include <string>
#include <memory>

class Object: public Entity
{
	std::vector<Mesh3D::ptr> meshes;
	unsigned int type;

public:

	virtual void loadDataFromFile(const char* filename) = 0;
	virtual void setMesh(Mesh3D::ptr mesh);
	virtual std::vector<Mesh3D::ptr>& getMeshes();
};

