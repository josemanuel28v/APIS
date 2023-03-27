#include "OrbitalLight.h"

OrbitalLight::OrbitalLight(glm::vec4 direction, glm::vec3 center, glm::vec3 color, Type type, float linearAtt, float radius)
{
	this->info.direction = direction;
	this->info.color = color;
	this->info.type = type;
	this->info.linearAtt = linearAtt;
	this->center = center;
	this->radius = radius;
	this->position = glm::vec4(center, 1.0);
}

void OrbitalLight::step(double deltaTime)
{
	static float angle = 0;

	position.x = center.x + radius * cos(angle);
	position.z = center.z + radius * sin(angle);

	angle += deltaTime;
}
