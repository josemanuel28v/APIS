#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "vertex_t.h"
#include "Material.h"

class GLSLMaterial: public Material
{
public:

	GLSLMaterial();
	virtual void loadPrograms(std::vector<std::string> fileNames) override;
	virtual void prepare() override;
};

