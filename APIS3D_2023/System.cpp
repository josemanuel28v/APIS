#include "System.h"
#include "GL1Render.h"
#include "GL4Render.h"
#include "GLFWInputManager.h"
#include "FactoryEngine.h"

Camera* System::camera = nullptr;
Render* System::render = nullptr;
InputManager* System::inputManager = nullptr;
std::vector<Object*>* System::objects = nullptr;
std::vector<Light*>* System::lights = nullptr;
std::vector<Emitter*>* System::emitters = nullptr;
glm::vec3 System::ambient = glm::vec3(0.1f, 0.1f, 0.1f);
bool System::end = false;
glm::mat4 System::modelMatrix;

void System::initSystem()
{
	render = FactoryEngine::getNewRender();
	inputManager = FactoryEngine::getNewInputManager();

	objects = new std::vector<Object*>();
	lights = new std::vector<Light*>();
	emitters = new std::vector<Emitter*>();

	render->init();

	// Setear la ventana de GL1Render o GL4Render a GLFWInputManager
	if (FactoryEngine::GetSelectedGraphicsBackend() == FactoryEngine::GL1 && FactoryEngine::GetSelectedInputBackend() == FactoryEngine::GLFW)
	{
		GL1Render* gl1Render = dynamic_cast<GL1Render*>(render);
		GLFWInputManager* glfwInput = dynamic_cast<GLFWInputManager*>(inputManager);

		glfwInput->setWindow(gl1Render->getWindow());
	}
	else if (FactoryEngine::GetSelectedGraphicsBackend() == FactoryEngine::GL4 && FactoryEngine::GetSelectedInputBackend() == FactoryEngine::GLFW)
	{
		GL4Render* gl4Render = dynamic_cast<GL4Render*>(render);
		GLFWInputManager* glfwInput = dynamic_cast<GLFWInputManager*>(inputManager);

		glfwInput->setWindow(gl4Render->getWindow());
	}

	inputManager->init();
}

void System::addObject(Object* obj)
{
	objects->push_back(obj);
}

void System::addEmitter(Emitter* emitter)
{
	emitters->push_back(emitter);
}

void System::removeObject(int objectIdx)
{
	delete (*objects)[objectIdx];
	objects->erase(objects->begin() + objectIdx);
}

void System::removeEmitter(int emitterIdx)
{
	delete (*emitters)[emitterIdx];
	emitters->erase(emitters->begin() + emitterIdx);
}

void System::exit()
{
	end = true;
}

void System::mainLoop()
{
	TimeManager t;

	// Setup objects
	for (const auto& obj : *objects)
	{
		render->setupObject(obj);
	}

	// Setup emitters particles
	for (const auto& emitter : *emitters)
	{
		render->setupObject(emitter->getPrototypeParticle());
	}

	while (!end) 
	{
		// Limpiar buffers
		render->clearDisplay();

		// Actualizar time manager
		t.update();

		// Actualizar cámara
		camera->step(t.getDeltaTime());

		// Actualzar objetos
		for (auto& object : *objects) 
		{
			object->step(t.getDeltaTime());
		}

		// Actualizar luces
		for (auto& light : *lights)
		{
			light->step(t.getTime());
		}

		// Actualizar emisores
		std::vector<Object*> particles(1);
		for (auto& emitter : *emitters)
		{
			emitter->step(t.getDeltaTime());
			for (auto& particle : *emitter->getParticleList())
			{
				particle->step(t.getDeltaTime());
				render->drawObject(particle);
			}
		}

		// Dibujar objetos
		render->drawObjects(objects);

		// Gestionar eventos
		glfwPollEvents();

		if (inputManager->isPressed('E') || render->isClosed()) exit();	
		if (inputManager->isWindowResized())
		{
			glm::ivec2 size = inputManager->getWindowSize();
			glViewport(0, 0, size.x, size.y);
			inputManager->setWindowResized();
			camera->setAspect((float)size.x / size.y);
			camera->computeProjectionMatrix();
		}	

		render->swapBuffers();
	}	 
}

void System::setCamera(Camera* camera)
{
	System::camera = camera;
}

Camera* System::getCamera()
{
	return camera;
}

glm::mat4 System::getModelMatrix()
{
	return modelMatrix;
}

void System::setModelMatrix(glm::mat4 newModelMatrix)
{
	modelMatrix = newModelMatrix;
}

const glm::vec3 System::getAmbient()
{
	return ambient;
}

void System::setAmbient(const glm::vec3& ambient)
{
	System::ambient = ambient;
}

std::vector<Light*>* System::getLights()
{
	return lights;
}

void System::addLight(Light* light)
{
	lights->push_back(light);
}

void System::removeLight(int lightIdx)
{
	delete (*lights)[lightIdx];
	lights->erase(lights->begin() + lightIdx);
}

void System::releaseMemory()
{
	if (camera) delete camera;
	if (render) delete render;
	if (inputManager) delete inputManager;

	// Liberar memoria del contenido del vector objects
	for (Object* obj : *objects)
	{
		delete obj;
	}

	// Liberar memoria del contenido del vector lights
	for (Light* light : *lights)
	{
		delete light;
	}

	// Vaciar vectores
	objects->clear();
	lights->clear();

	// Liberar memoria del los vectores
	delete objects;
	delete lights;

	camera = nullptr;
	render = nullptr;
	inputManager = nullptr;
	objects = nullptr;
	lights = nullptr;
}
