#include "Emitter.h"
#include "System.h"
#include "State.h"

Emitter::Emitter(const char* mshFile, bool autoFade)
{
	this->autoFade = autoFade;
	this->mshFile = mshFile;
	this->particleAccum = 0.0f;
	this->particles = new std::list<Particle*>();
	this->emitting = true;

	this->prototype = new Particle(mshFile, glm::vec3(0.0f), 0.0f, 0.0f, 0.0f, false);
}

void Emitter::setRateRange(float min, float max)
{
	this->minRate = min;
	this->maxRate = max;
}

void Emitter::setVelocityRange(const glm::vec3& min, const glm::vec3& max)
{
	this->minVel = min;
	this->maxVel = max;
}

void Emitter::setSpinVelocityRange(float min, float max)
{
	this->minSpin = min;
	this->maxSpin = max;
}

void Emitter::setScaleRange(float min, float max)
{
	this->minScale = min;
	this->maxScale = max;
}

void Emitter::setLifeTimeRange(float min, float max)
{
	this->minLifeTime = min;
	this->maxLifeTime = max;
}

void Emitter::setColorRange(const glm::vec4& min, const glm::vec4& max)
{
	this->minColor = min;
	this->maxColor = max;
}

std::list<Particle*>* Emitter::getParticleList()
{
	return particles;
}

void Emitter::step(double deltaTime)
{
	// Generar part�culas si se est� emitiendo
	if (emitting)
	{
		float emissionRate = glm::linearRand(minRate, maxRate);
		float newParticleCount = particleAccum + emissionRate * deltaTime;
		int particlesToCreate = (int)newParticleCount;
		particleAccum = newParticleCount - particlesToCreate;

		for (int i = 0; i < particlesToCreate; ++i)
		{
			float randSpin = glm::linearRand(minSpin, maxSpin);
			double randLifeTime = glm::linearRand(minLifeTime, maxLifeTime);
			float randScale = glm::linearRand(minScale, maxScale);
			glm::vec3 randVelocity = glm::vec3(glm::linearRand(minVel.x, maxVel.x),
											   glm::linearRand(minVel.y, maxVel.y),
											   glm::linearRand(minVel.z, maxVel.z));
			// Falta el color
			Particle* p = new Particle(mshFile, randVelocity, randSpin, randLifeTime, randScale, autoFade);
			p->setPosition(this->getPosition());
			particles->push_back(p);
		}
	}

	// Ordenar part�culas por distancia a la c�mara
	std::map<float, Particle*> distMap;
	for (Particle* p : *particles)
	{
		if (p->getRemainingLifeTime() > 0)
		{
			float dist = glm::distance(glm::vec3(p->getPosition()), glm::vec3(System::getCamera()->getPosition()));
			distMap[dist] = p;
		}
		else
		{
			delete p;
		}
	}

	particles->clear();

	for (auto p : distMap)
	{
		particles->push_back(p.second);
	}
}

bool Emitter::isEmitting()
{
	return emitting;
}