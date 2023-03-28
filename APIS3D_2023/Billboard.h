#pragma once

#include "Object.h"
#include "Camera.h"

class Billboard : public Object
{
public:
	Billboard(std::string mshFile);
	float getSpin() const { return spin; }
	float setSpin(float spin) { this->spin = spin; }
	void computeModelMatrix() override;
	virtual void step(double deltaTime) = 0;

protected:
	float spin;
};

