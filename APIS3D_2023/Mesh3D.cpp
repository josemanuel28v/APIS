#include "Mesh3D.h"

unsigned int Mesh3D::counter = 0;

Mesh3D::Mesh3D()
{
	meshID = counter++;
	vVertList = new std::vector<vertex_t>();
	vTriangleIdxList = new std::vector<glm::uint32>();
	mat = nullptr;
}

Mesh3D::~Mesh3D()
{
	if (mat) delete mat;

	vVertList->clear();
	vTriangleIdxList->clear();

	delete vVertList;
	delete vTriangleIdxList;

	mat = nullptr;
	vVertList = nullptr;
	vTriangleIdxList = nullptr;
}

unsigned int Mesh3D::getMeshID()
{
	return meshID;
}

void Mesh3D::addVertex(vertex_t v)
{
	vVertList->push_back(v);
}

std::vector<struct vertex_t>* Mesh3D::getVertList()
{
	return vVertList;
}

Material* Mesh3D::getMaterial()
{
	return mat;
}

void Mesh3D::setMaterial(Material* mat)
{
	this->mat = mat;
}

void Mesh3D::setVertexList(std::vector<glm::uint32>* vList)
{
	vTriangleIdxList = vList;
}

void Mesh3D::setDepthTestEnabled(bool depthTestEnabled)
{
	this->depthTestEnabled = depthTestEnabled;
}

bool Mesh3D::getDepthTestEnabled()
{
	return depthTestEnabled;
}

std::vector<glm::uint32>* Mesh3D::getTriangleIdxList()
{
	return vTriangleIdxList;
}

void Mesh3D::addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3)
{
	//Agregamos los 3 puntos al final de la lista vTriangleIdxList
	vTriangleIdxList->push_back(vId1);
	vTriangleIdxList->push_back(vId2);
	vTriangleIdxList->push_back(vId3);
}
