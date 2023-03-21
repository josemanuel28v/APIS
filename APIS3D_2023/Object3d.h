#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Object.h"
#include "pugixml.hpp"

class Object3D : public Object
{
public:
	virtual void loadDataFromFile(const char* filename) override;
	virtual void step(double deltaTime) override {}
};

