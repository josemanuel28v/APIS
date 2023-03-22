#pragma once

#include "Billboard.h"
#include "Camera.h"

class Particle : public Billboard
{
public:
	Particle(std::string mshFile, glm::vec3 vel, float spinVel, double lifeTime, float scale, bool autoFade);
	float getRemainingLifeTime() const;
	float getTotalLifeTime() const;
	virtual void step(double deltaTime) override;

private:
	glm::vec3 velocity;
	double lifeTime;
	double maxLifeTime;
	bool autoFade;
};

