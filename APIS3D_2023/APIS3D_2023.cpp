#include <iostream>
#include "common.h" // �nico sitio donde se define la implementacion de glad
#include "System.h"
#include "FactoryEngine.h"
#include "CubeTex.h"
#include "CameraKeyboard.h"
#include "OrbitalLight.h"
#include "Emitter.h"
#include "InstancedEmitter.h"
#include "OrbitalCamera.h"

void mainP5()
{
    // Seleccionar backends a utilizar
    FactoryEngine::SetSelectedGraphicsBackend(FactoryEngine::GraphicsBackend::GL4);
    FactoryEngine::SetSelectedInputBackend(FactoryEngine::InputBackend::GLFW);

    // Inicializar c�mara
    glm::vec3 position = glm::vec3(0.0f, 5.0f, 5.0f);
    glm::vec3 lookAt = glm::vec3(0.0f, 5.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    Camera* camera = new CameraKeyboard(Camera::ProjectionType::PERSPECTIVE, position, up, lookAt);
    //Camera* camera = new OrbitalCamera(Camera::PERSPECTIVE, position.y, up, lookAt, 5);

    // Inicializar sistema (backends)
    System::initSystem();

    // Luz
    System::addLight(new Light(glm::vec3(-3, 3, 0), glm::vec3(1.0f), Light::POINT, 1.0f, 0.1f));

    // Totem
    Object3D* totem1 = new Object3D("data/column.msh");
    totem1->setScaling(glm::vec4(0.01f));
    totem1->setPosition(glm::vec4(-2.0, 0.0f, 0.0f, 1.0f));

    Object3D* totem2 = new Object3D("data/column.msh");
    totem2->setScaling(glm::vec4(0.01f));
    totem2->setPosition(glm::vec4(2.0, 0.0f, 0.0f, 1.0f));

    // Emisores
    Emitter* smokeEmitter = new Emitter("data/smoke.msh", true);
    InstancedEmitter* smokeEmitterInstanced = new InstancedEmitter("data/smoke_instancing.msh", true);
    Emitter* flameEmitter = new Emitter("data/flame.msh", true);
    InstancedEmitter* flameEmitterInstanced = new InstancedEmitter("data/flame_instancing.msh", true);

    smokeEmitter->setPosition(glm::vec4(-2.0f, 7.0f, 0.0f, 1.0f));
    smokeEmitter->setRateRange(5, 10);
    smokeEmitter->setLifeTimeRange(1, 5);
    smokeEmitter->setVelocityRange(glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f));
    smokeEmitter->setSpinVelocityRange(glm::radians(30.0f), glm::radians(60.0f));
    smokeEmitter->setScaleRange(0.05f, 0.1f);

    smokeEmitterInstanced->setPosition(glm::vec4(2.0f, 7.0f, 0.0f, 1.0f));
    smokeEmitterInstanced->setRateRange(5, 10);
    smokeEmitterInstanced->setLifeTimeRange(1, 5);
    smokeEmitterInstanced->setVelocityRange(glm::vec3(-0.1f, 1.0f, -0.1f), glm::vec3(0.1f, 4.0f, 0.1f));
    smokeEmitterInstanced->setSpinVelocityRange(glm::radians(30.0f), glm::radians(60.0f));
    smokeEmitterInstanced->setScaleRange(0.05f, 0.1f);

    flameEmitter->setPosition(glm::vec4(-2.0f, 7.0f, 0.0f, 1.0f));
    flameEmitter->setRateRange(10, 25);
    flameEmitter->setLifeTimeRange(0.5f, 0.5f);
    flameEmitter->setVelocityRange(glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f));
    flameEmitter->setSpinVelocityRange(glm::radians(0.0f), glm::radians(0.0f));
    flameEmitter->setScaleRange(0.025f, 0.1f);

    flameEmitterInstanced->setPosition(glm::vec4(2.0f, 7.0f, 0.0f, 1.0f));
    flameEmitterInstanced->setRateRange(10, 25);
    flameEmitterInstanced->setLifeTimeRange(0.5f, 0.5f);
    flameEmitterInstanced->setVelocityRange(glm::vec3(-1.0f, 5.0f, -1.0f), glm::vec3(1.0f, 10.0f, 1.0f));
    flameEmitterInstanced->setSpinVelocityRange(glm::radians(0.0f), glm::radians(0.0f));
    flameEmitterInstanced->setScaleRange(0.025f, 0.1f);

    smokeEmitterInstanced->setMaxParticles(200);
    flameEmitterInstanced->setMaxParticles(200);

    System::addObject(totem1);
    System::addEmitter(smokeEmitter);
    System::addEmitter(flameEmitter);

    System::addObject(totem2);
    System::addInstancedEmitter(smokeEmitterInstanced);
    System::addInstancedEmitter(flameEmitterInstanced);

    // A�adir objetos al sistema y lanzar el bucle de dibujado
    System::setAmbient(glm::vec3(0.2, 0.2, 0.2));
    System::setCamera(camera);
    System::mainLoop();
    System::releaseMemory();
}

void mainP6()
{
    // Seleccionar backends a utilizar
    FactoryEngine::SetSelectedGraphicsBackend(FactoryEngine::GraphicsBackend::GL4);
    FactoryEngine::SetSelectedInputBackend(FactoryEngine::InputBackend::GLFW);

    // Inicializar c�mara
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 4.0f);
    glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    Camera* camera = new CameraKeyboard(Camera::ProjectionType::PERSPECTIVE, position, up, lookAt);
    //Camera* camera = new OrbitalCamera(Camera::PERSPECTIVE, position.y, up, lookAt, 2);

    // Inicializar sistema (backends)
    System::initSystem();

    // Luz
    System::addLight(new Light(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(1.0f), Light::POINT, 2.0f, 0.01f));

    Object3D* skybox = new Object3D("data/skybox.msh");
    Object3D* suzanne = new Object3D("data/suzanne_refract.msh");
    Object3D* suzanneRefractReflect = new Object3D("data/suzanne_refract_reflect.msh");
    Object3D* cube = new Object3D("data/normalMapCube.msh");
    Object3D* cubeReflect = new Object3D("data/normalMapCubeReflection.msh");
    Object3D* teapot = new Object3D("data/teapot_reflect.msh");

    skybox->setScaling(glm::vec4(30.0f));

    suzanne->setPosition(glm::vec4(-6.0f, 0.0f, 0.0f, 1.0f));
    suzanneRefractReflect->setPosition(glm::vec4(-3.0f, 0.0f, 0.0f, 1.0f));
    cube->setPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    cubeReflect->setPosition(glm::vec4(3.0f, 0.0f, 0.0f, 1.0f));
    teapot->setPosition(glm::vec4(6.0f, 0.0f, 0.0f, 1.0f));

    // A�adir objetos al sistema y lanzar el bucle de dibujado
    System::addObject(skybox);
    System::addObject(suzanne);
    System::addObject(teapot);
    System::addObject(cube);
    System::addObject(cubeReflect);
    System::addObject(suzanneRefractReflect);
    System::setAmbient(glm::vec3(0.2, 0.2, 0.2));
    System::setCamera(camera);
    System::mainLoop();
    System::releaseMemory();
}

int main(int argc, char** argv)
{
    //mainP5();
    mainP6();
}
