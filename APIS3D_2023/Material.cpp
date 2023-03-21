#include "Material.h"

Texture* Material::getTexture()
{
    return colorTexture;
}

void Material::setTexture(Texture* texture)
{
    this->colorTexture = texture;
}

Material::normalType Material::getNormalType()
{
    return normType;
}

void Material::setNormalType(normalType type)
{
    this->normType = type;
}

// Si se comparten programas entre materiales entonces el destructor no sabrá si ese program se ha destruido o no por lo que habrá errores de ejecución
// esto se podría tratar con punteros inteligentes (shared_ptr)
void Material::setProgram(RenderProgram* program)
{
    //if (this->program) delete this->program;
    //
    //this->program = program;
}

RenderProgram* Material::getProgram()
{
    return program;
}

const glm::vec4& Material::getColor() const
{
    return color;
}

void Material::setColor(const glm::vec4& color)
{
    this->color = color;
}

uint8_t Material::getShininess() const
{
    return shininess;
}

void Material::setShininess(uint8_t shininess)
{
    this->shininess = shininess;
}

Material::~Material()
{
    if (colorTexture) delete colorTexture;
    if (normalMap) delete normalMap;
    if (program) delete program;

    colorTexture = nullptr;
    normalMap = nullptr;
    program = nullptr;
}

void Material::setIsTextured(bool isTextured)
{
    this->isTextured = isTextured;
}

bool Material::getIsTextured()
{
    return isTextured;
}
