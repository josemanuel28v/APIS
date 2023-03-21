#include "Camera.h"

void adjustPitchYaw(float& pitch, float& yaw, float& roll)
{
	pitch = fmod(pitch, 2.0f * M_PI); // Dejar el valor dentro del rango -360, 360
	bool invYaw = false;

	if (pitch > M_PI)
	{
		pitch = M_PI - pitch;
		invYaw = !invYaw;
		std::cout << "adjust 1" << std::endl;
	}
	else if (pitch < -M_PI)
	{
		pitch = - pitch - M_PI;
		invYaw = !invYaw;
		std::cout << "adjust 2" << std::endl;
	}

	if (pitch > M_PI_2)
	{
		pitch = M_PI - pitch;
		pitch *= -1;
		yaw *= -1;
		invYaw = !invYaw;

		std::cout << "adjust 3" << std::endl;
	}
	else if (pitch < -M_PI_2)
	{
		pitch = -pitch - M_PI;
		invYaw = !invYaw;
		pitch *= -1;
		yaw *= -1;
		std::cout << "adjust 4" << std::endl;
	}

	if (invYaw) yaw += M_PI;
}

Camera::Camera(ProjectionType type, glm::vec3 position, glm::vec3 worldUp, glm::vec3 lookAt)
{
	this->type = type;
	this->position = glm::vec4(position.x, position.y, position.z, 1.0);
	this->worldUp = worldUp;
	this->lookAt = lookAt;
	this->fov = 90.0f;
	this->aspect = 4.0f / 3.0f;
	this->near = 0.1f;
	this->far = 200.0f;
	this->forward = glm::normalize(lookAt - glm::vec3(position));

	// Initialize camera rotation with the initial rotation of forward vector
	this->rotation = glm::vec4(
		glm::atan(forward.y, glm::sqrt(forward.x * forward.x + forward.z * forward.z)),
		glm::atan(forward.z, forward.x),
		0.0f, 
		0.0f
	);

	updateCameraVectors();
	computeViewMatrix();
	computeProjectionMatrix();
}

glm::mat4 Camera::getProjection()
{
	return projection;
}

glm::mat4 Camera::getView()
{
	return view;
}

void Camera::computeProjectionMatrix()
{
	switch (type)
	{
	case ORTOGRAPHIC:
		//projection = glm::ortho();
		break;

	case PERSPECTIVE:
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
		break;
	}
}

void Camera::computeViewMatrix()
{
	this->view = glm::lookAt(glm::vec3(position), lookAt, up);
}

void Camera::setFov(float fov)
{
	this->fov = fov;
}

void Camera::setAspect(float aspect)
{
	this->aspect = aspect;
}

void Camera::setNear(float near)
{
	this->near = near;
}

void Camera::setFar(float far)
{
	this->far = far;
}

void Camera::updateCameraVectors()
{
	forward.x = glm::cos(rotation.y) * glm::cos(rotation.x);
	forward.y = glm::sin(rotation.x);
	forward.z = glm::sin(rotation.y) * glm::cos(rotation.x);

	forward = glm::normalize(forward);
	right = glm::normalize(glm::cross(forward, worldUp));  
	up = glm::normalize(glm::cross(right, forward));
}
