#include "Material.h"



Material::~Material()
{
    if (colorMap) delete colorMap;
    if (normalMap) delete normalMap;
    if (program) delete program;

    colorMap = nullptr;
    normalMap = nullptr;
    program = nullptr;
}

void Material::setTexturing(bool texturing)
{
    this->texturing = texturing;
}

void Material::setLighting(bool lighting)
{
    this->lighting = lighting;
}

void Material::setCulling(bool culling)
{
    this->culling = culling;
}

void Material::setDepthWrite(bool depthWrite)
{
    this->depthWrite = depthWrite;
}

void Material::setBlendMode(BlendMode blendMode)
{
    this->blendMode = blendMode;
}

void Material::setNormalMode(NormalMode normalMode)
{
    this->normalMode = normalMode;
}

void Material::setTexture(Texture* colorMap)
{
    this->colorMap = colorMap;
}

/* 
    Si se comparten programas entre materiales entonces el destructor no sabrá si ese program se ha destruido o no por lo que habrá errores de ejecución
    esto se podría tratar con punteros inteligentes (shared_ptr)
*/
void Material::setProgram(RenderProgram* program)
{
    this->program = program;
}

void Material::setColor(glm::vec4 color)
{
    this->color = color;
}

void Material::setShininess(uint8_t shininess)
{
    this->shininess = shininess;
}

bool Material::getTexturing() const
{
    return texturing;
}

bool Material::getLighting() const
{
    return lighting;
}

bool Material::getCulling() const
{
    return culling;
}

bool Material::getDepthWrite() const
{
    return depthWrite;
}

Material::BlendMode Material::getBlendMode() const
{
    return blendMode;
}

Material::NormalMode Material::getNormalMode() const
{
    return normalMode;
}

Texture* Material::getTexture() const
{
    return colorMap;
}

RenderProgram* Material::getProgram() const
{
    return program;
}

glm::vec4 Material::getColor() const
{
    return color;
}

uint8_t Material::getShininess() const
{
    return shininess;
}

