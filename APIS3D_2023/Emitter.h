#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Particle.h"
#include "Entity.h"

class Emitter : public Entity
{
public:
	Emitter(const char* mshFile, bool autoFade);

	void setRateRange(float min, float max);
	void setVelocityRange(const glm::vec3& min, const glm::vec3& max);
	void setSpinVelocityRange(float min, float max);
	void setScaleRange(float min, float max);
	void setLifeTimeRange(float min, float max);
	void setColorRange(const glm::vec4& min, const glm::vec4& max);
	void emit(bool emitting);

	Particle* getPrototypeParticle() { return prototype; }
	std::list<Particle*>* getParticleList();
	bool getAutoFade() { return autoFade; }
	virtual void step(double deltaTime) override;

	void setMaxParticles(unsigned maxNumParticles) 
	{
		if (mvps) delete mvps;
		this->maxNumParticles = maxNumParticles;
		mvps = new glm::mat4[maxNumParticles];
	}
	unsigned getNumParticles()
	{
		return currentNumParticles;
	}

	glm::mat4* getMVPArray() { return mvps; }

	bool isEmitting();

private:
	std::list<Particle*>* particles;
	Particle* prototype;

	unsigned currentNumParticles;
	unsigned maxNumParticles;
	glm::mat4* mvps;

	const char* mshFile;
	float particleAccum;
	bool autoFade;

	float minRate;
	float maxRate;
	float minSpin;
	float maxSpin;
	float minScale;
	float maxScale;
	float minLifeTime;
	float maxLifeTime;
	glm::vec3 minVel;
	glm::vec3 maxVel;
	glm::vec3 minColor;
	glm::vec3 maxColor;

	bool emitting;
};

