#include "GLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLTexture::GLTexture() : Texture()
{}

GLTexture::GLTexture(std::string fileName) : GLTexture()
{
	load(fileName);
}

GLuint GLTexture::getID()
{
    return this->textID;
}

void GLTexture::bind()
{
    glActiveTexture(GL_TEXTURE0 + textUnit);
    glBindTexture(GL_TEXTURE_2D, textID);
}

void GLTexture::load(std::string fileName) 
{
	int comp = 0;
	color32_t* pixels = (color32_t*)stbi_load(fileName.c_str(), &size.x, &size.y, &comp, 4);

	glGenTextures(1, &textID);
	glBindTexture(GL_TEXTURE_2D, textID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	stbi_image_free(pixels);
}
