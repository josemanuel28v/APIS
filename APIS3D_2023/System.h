#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Camera.h"
#include "Render.h"
#include "InputManager.h"
#include "Object.h"
#include "Light.h"
#include "Emitter.h"

class TimeManager {

	double newTime = 0;
	double deltaTime = 0;
	double lastTime = 0;

public:

	void update() 
	{
		newTime = glfwGetTime();
		deltaTime = newTime - lastTime;
		lastTime = newTime;
	}

	double getDeltaTime()
	{
		return deltaTime;
	}

	double getTime()
	{
		return newTime;
	}
};

class System
{
public:

	static Camera* camera;
	static Render* render;
	static InputManager* inputManager;
	static std::vector<Object*>* objects;
	static std::vector<Light*>* lights;
	static std::vector<Emitter*>* emitters;
	static bool end;
	static glm::mat4 modelMatrix;
	static glm::vec3 ambient;

	static void initSystem();
	static void mainLoop();
	static void exit();
	static void releaseMemory();

	static void addLight(Light* light);
	static void addObject(Object* obj);
	static void addEmitter(Emitter* emitter);

	static void removeLight(int lightIdx);
	static void removeObject(int objectIdx);
	static void removeEmitter(int emitterIdx);

	static void setCamera(Camera* camera);
	static void setModelMatrix(glm::mat4 newModelMatrix);
	static void setAmbient(const glm::vec3& ambient);

	static Camera* getCamera();
	static glm::mat4 getModelMatrix();
	static const glm::vec3 getAmbient();
	static std::vector<Light*>* getLights();



	
};

