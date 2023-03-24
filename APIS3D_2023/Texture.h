#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"

class Texture
{
public:
	Texture() { textUnit = textUnitCounter++; }
	glm::ivec2 getSize();
	void setSize(glm::ivec2 size);
	virtual GLuint getID() = 0;
	virtual void bind() = 0;
	virtual void load(std::string fileName) = 0;
	unsigned getTextureUnit() { return textUnit; }

protected:
	GLuint textID;
	glm::ivec2 size;
	unsigned textUnit;
	inline static unsigned textUnitCounter = 0;
};

