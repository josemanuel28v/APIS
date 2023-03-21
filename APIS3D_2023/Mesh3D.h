#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Entity.h"
#include "vertex_t.h"
#include "Material.h"

class Mesh3D
{
	static unsigned int counter;

	unsigned int meshID;
	std::vector<vertex_t>* vVertList;
	std::vector<glm::uint32>* vTriangleIdxList;
	Material* mat;

	bool depthTestEnabled = true;

public:
	Mesh3D();
	virtual ~Mesh3D();
	unsigned int getMeshID();
	void addVertex(vertex_t);
	std::vector<struct vertex_t>* getVertList();
	Material* getMaterial();
	void setMaterial(Material* mat);
	void setVertexList(std::vector<glm::uint32>* vList);
	void setDepthTestEnabled(bool depthTestEnabled);
	bool getDepthTestEnabled();
	std::vector<glm::uint32>* getTriangleIdxList();
	void addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3);
};
