#include "Texture.h"

glm::ivec2 Texture::getSize()
{
    return size;
}

void Texture::setSize(glm::ivec2 size)
{
    this->size = size;
}

