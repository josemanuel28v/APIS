#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Particle.h"
#include "Entity.h"

class Emitter : public Entity
{
public:
	Emitter(const char* mshFile, bool autoFade);
	virtual ~Emitter();
	virtual void setRateRange(float min, float max);
	virtual void setVelocityRange(const glm::vec3& min, const glm::vec3& max);
	virtual void setSpinVelocityRange(float min, float max);
	virtual void setScaleRange(float min, float max);
	virtual void setLifeTimeRange(float min, float max);
	virtual void setColorRange(const glm::vec4& min, const glm::vec4& max);
	virtual void emit(bool emitting) { this->emitting = emitting; }

	virtual Particle* getPrototypeParticle() { return prototype; }
	virtual std::list<Particle*>* getParticleList();
	virtual bool getAutoFade() { return autoFade; }
	bool isEmitting();
	virtual void step(double deltaTime) override;

protected:
	std::list<Particle*>* particles;
	Particle* prototype;

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

