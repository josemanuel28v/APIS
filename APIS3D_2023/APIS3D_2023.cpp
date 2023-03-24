#include <iostream>
#include "common.h" // Único sitio donde se define la implementacion de glad
#include "System.h"
#include "FactoryEngine.h"
#include "CubeTex.h"
#include "CameraKeyboard.h"
#include "OrbitalLight.h"
#include "Emitter.h"

int main(int argc, char** argv)
{
    // Seleccionar backends a utilizar
    FactoryEngine::SetSelectedGraphicsBackend(FactoryEngine::GraphicsBackend::GL4);
    FactoryEngine::SetSelectedInputBackend(FactoryEngine::InputBackend::GLFW);

    // Inicializar cámara
    glm::vec3 position = glm::vec3(0.0f, 5.0f, 5.0f);
    glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    Camera* camera = new CameraKeyboard(Camera::ProjectionType::PERSPECTIVE, position, glm::vec3(0.0f, 1.0f, 0.0f), lookAt);
     
    // Inicializar sistema (backends)
    System::initSystem();

    // Luz
    System::addLight(new Light(glm::vec4(0.0f), glm::vec3(-4, 4, 0), glm::vec3(1.0f), Light::POINT, 0.5f));

    // Totem
    Object3D* totem = new Object3D();
    totem->loadDataFromFile("data/column.msh");
    totem->setScaling(glm::vec4(0.01f));

    // Emisores
    Emitter* smokeEmitter = new Emitter("data/smoke.msh", true);
    Emitter* flameEmitter = new Emitter("data/flame.msh", true);

    smokeEmitter->setPosition(glm::vec4(0.0f, 7.0f, 0.0f, 1.0f));
    smokeEmitter->setRateRange(5, 10);
    smokeEmitter->setLifeTimeRange(1, 5);
    smokeEmitter->setVelocityRange(glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f));
    smokeEmitter->setSpinVelocityRange(glm::radians(30.0f), glm::radians(60.0f));
    smokeEmitter->setScaleRange(0.05f, 0.1f);

    flameEmitter->setPosition(glm::vec4(0.0f, 7.0f, 0.0f, 1.0f));
    flameEmitter->setRateRange(10, 25);
    flameEmitter->setLifeTimeRange(0.5f, 0.5f);
    flameEmitter->setVelocityRange(glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f));
    flameEmitter->setSpinVelocityRange(glm::radians(0.0f), glm::radians(0.0f));
    flameEmitter->setScaleRange(0.025f, 0.1f);

    smokeEmitter->setMaxParticles(200);
    flameEmitter->setMaxParticles(200);

    System::addObject(totem);
    System::addEmitter(smokeEmitter);
    System::addEmitter(flameEmitter);

    // Añadir objetos al sistema y lanzar el bucle de dibujado
    System::setAmbient(glm::vec3(0.2, 0.2, 0.2));
    System::setCamera(camera);
    System::mainLoop();
    System::releaseMemory();
}
