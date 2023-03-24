#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Texture.h"
#include "pugixml.hpp"

struct color32_t {
	unsigned char r, g, b, a;
};

class GLTexture: public Texture
{
public:
	GLTexture();
	GLTexture(std::string fileName);
	virtual GLuint getID() override;
	virtual void bind() override;
	virtual void load(std::string fileName) override;
};

