#pragma once
#include "Entity.h"
#include "Mesh3D.h"
#include <string>

class Object: public Entity
{
	std::vector<Mesh3D*> meshes;
	unsigned int type;

public:

	virtual ~Object();
	virtual void loadDataFromFile(const char* filename) = 0;
	virtual void setMesh(Mesh3D* mesh);
	virtual std::vector<Mesh3D*>& getMeshes();
};

