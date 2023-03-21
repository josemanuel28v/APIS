#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"

class Entity
{
	glm::mat4 modelMt;

protected:

	glm::vec4 position;
	glm::vec4 rotation; 
	glm::vec4 scaling;  
	
public:

	Entity();
	void computeModelMatrix();
	virtual void step(double deltaTime) = 0;

	void setPosition(glm::vec4 position);
	void setRotation(glm::vec4 rotation);
	void setScaling(glm::vec4 scaling);
	void setModelMt(glm::mat4 modelMt);

	glm::vec4 getPosition();
	glm::vec4 getRotation();
	glm::vec4 getScaling();
	glm::mat4 getModelMt();
};

