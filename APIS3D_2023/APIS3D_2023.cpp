#include <iostream>
#include "common.h" // Único sitio donde se define la implementacion de glad
#include "System.h"
#include "FactoryEngine.h"
#include "CubeTex.h"
#include "CameraKeyboard.h"
#include "OrbitalLight.h"

int main(int argc, char** argv)
{
    // Seleccionar backends a utilizar
    FactoryEngine::SetSelectedGraphicsBackend(FactoryEngine::GraphicsBackend::GL4);
    FactoryEngine::SetSelectedInputBackend(FactoryEngine::InputBackend::GLFW);

    // Inicializar cámara
    glm::vec3 position = glm::vec3(0.0f, 3.0f, 3.0f);
    glm::vec3 lookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    Camera* camera = new CameraKeyboard(Camera::ProjectionType::PERSPECTIVE, position, glm::vec3(0.0f, 1.0f, 0.0f), lookAt);
     
    // Inicializar sistema (backends)
    System::initSystem();

    // Iluminación
    System::addLight(new Light(
        glm::vec4(1.0f, 1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 1.0f), 
        Light::DIRECTIONAL,
        1.0f
    ));

    System::addLight(new OrbitalLight(
        glm::vec4(1.0f, 1.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f),
        Light::POINT,
        0.2,
        5)
    );

    // Crear cubo
    CubeTex* cube = new CubeTex();
    cube->setPosition(glm::vec4(0.75f, 0.0f, 0.0f, 1.0f));

    // Crear bunny
    Object3D* bunny = new Object3D();
    //bunny->loadDataFromFile("data/bunny.msh");
    bunny->setPosition(glm::vec4(-0.75f, -0.5f, 0.0f, 1.0f));
    bunny->setScaling(glm::vec4(10.0f, 10.0f, 10.0f, 1.0f));
    bunny->setRotation(glm::vec4(M_PI * 0.5, 0.0f, 0.0f, 1.0f));

    // Crear asian town
    Object3D* town = new Object3D();
    //town->loadDataFromFile("data/asian_town.msh");
    town->setScaling(glm::vec4(10.0f, 10.0f, 10.0f, 1.0f));

    Object3D* ground = new Object3D();
    ground->loadDataFromFile("data/ground.msh");
    ground->setScaling(glm::vec4(25.0f, 1.0f, 25.0f, 1.0f));
    ground->setPosition(glm::vec4(0.0f, -0.5f, 0.0f, 1.0f));

    // Añadir objetos al sistema y lanzar el bucle de dibujado
    System::setAmbient(glm::vec3(0.2, 0.2, 0.2));
    System::setCamera(camera);
    System::addObject(cube);
    System::addObject(ground);
    //System::addObject(bunny);
    //System::addObject(town);
    System::mainLoop();
    System::releaseMemory();
}
