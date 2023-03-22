#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "Entity.h"
#include "vertex_t.h"
#include "Material.h"

class Mesh3D
{
	static unsigned int counter;

	unsigned int id;
	std::vector<vertex_t>* vertices;
	std::vector<glm::uint32>* indices;
	Material* material;

public:
	using ptr = std::shared_ptr<Mesh3D>;

	Mesh3D();
	virtual ~Mesh3D();

	virtual void addVertex(vertex_t);
	virtual void addTriangle(glm::uint32 id1, glm::uint32 id2, glm::uint32 id3);

	virtual std::vector<struct vertex_t>* getVertices();
	virtual std::vector<glm::uint32>* getIndices();
	virtual Material* getMaterial();
	virtual unsigned int getMeshID();

	virtual void setVertices(std::vector<struct vertex_t>* vertices);
	virtual void setIndices(std::vector<glm::uint32>* indices);
	virtual void setMaterial(Material* material);	
};
