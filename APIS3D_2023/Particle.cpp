#include "Particle.h"

Particle::Particle(std::string mshFile, glm::vec3 vel, float spinVel, double lifeTime, float scale, bool autoFade) : Billboard(mshFile)
{
	this->velocity = vel;
	this->spin = spinVel;
	this->lifeTime = lifeTime;
	this->maxLifeTime = lifeTime;
	this->autoFade = autoFade;

	glm::ivec2 texSize(1);
	for (Mesh3D::ptr mesh : getMeshes())
	{
		Texture* text = mesh->getMaterial()->getTexture();
		if (text != nullptr)
		{
			texSize = text->getSize();
		}
	}

	// Escalado en función del tamaño de la textura
	this->scaling = glm::vec4(scale * texSize.x, scale * texSize.y, 1.0f, 1.0f);
}

float Particle::getRemainingLifeTime() const
{
	return lifeTime;
}

float Particle::getTotalLifeTime() const
{
	return maxLifeTime;
}

void Particle::step(double deltaTime)
{
	position += glm::vec4(velocity * (float)deltaTime, 1.0f);
	rotation.z += spin * deltaTime;
	lifeTime -= deltaTime;
}

void Particle::updateAlpha()
{
	// Deberia setearse el alpha del color de la mesh justo antes de pintar si se comparte Mesh
	if (autoFade)
	{
		float normLifeTime = lifeTime / maxLifeTime;
		for (auto mesh : getMeshes())
		{
			Material* mat = mesh->getMaterial();
			glm::vec4 color = mat->getColor();
			color.a = normLifeTime;
			mat->setColor(color);
		}
	}
}
