#include "TrianguloRot.h"
#include "FactoryEngine.h"

TrianguloRot::TrianguloRot()
{
    Mesh3D* triangle_mesh = new Mesh3D();
    vertex_t v1, v2, v3;

    // Definir posici�n de los v�rtices del triangulo
    v1.position = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
    v2.position = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f);
    v3.position = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f);

    // A�adir los v�rtices a la malla y establecer su color
    triangle_mesh->addVertex(v1);
    triangle_mesh->addVertex(v2);
    triangle_mesh->addVertex(v3);
    triangle_mesh->addTriangle(0, 1, 2);

    Material* mat = FactoryEngine::getNewMaterial();
    triangle_mesh->setMaterial(mat);

    mat->loadPrograms({"data/default.vertex", "data/default.fragment"});

    // A�adir la malla al objeto y establecer atributos b�sicos
    setMesh(triangle_mesh);
}

void TrianguloRot::step(double deltaTime)
{
    float rotationVelocity = 1;
    rotation.y += rotationVelocity * deltaTime;
}
