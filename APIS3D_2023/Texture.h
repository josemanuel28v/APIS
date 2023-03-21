#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"

class Texture
{
public:
	glm::ivec2 getSize();
	void setSize(glm::ivec2 size);
	virtual GLuint getID() = 0;
	virtual void bind(GLuint textureUnit) = 0;
	virtual void load(std::string fileName) = 0;

protected:
	GLuint textID;
	glm::ivec2 size;
};

