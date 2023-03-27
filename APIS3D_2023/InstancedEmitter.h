#pragma once
#include "Emitter.h"

class InstancedEmitter : public Emitter
{
public:
	InstancedEmitter(const char* mshFile, bool autoFade) : Emitter(mshFile, autoFade) {}
	virtual ~InstancedEmitter();

	void setMaxParticles(unsigned maxNumParticles);

	unsigned getNumParticles() { return currentNumParticles; };
	glm::mat4* getMVPArray() { return mvps; }
	glm::vec4* getColorArray() { return colors; }

	virtual void step(double deltaTime) override;

private:

	unsigned currentNumParticles;
	unsigned maxNumParticles;
	glm::mat4* mvps;
	glm::vec4* colors;
};

