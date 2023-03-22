#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "GL1Render.h"

struct VBO_t
{
	unsigned int id;   // Id del vertex buffer object
	unsigned int v_id; // Id del buffer de vertices
	unsigned int i_id; // Id del buffer de indices
};

class GL4Render : public GL1Render
{
public:
	GL4Render(int width, int height) : GL1Render(width, height) {};
	virtual void setupObject(Object* obj) override;
	virtual void removeObject(Object* obj) override;
	virtual void drawObject(Object* obj) override;
	virtual void drawObjects(std::vector<Object*>* objs) override;

private:
	std::unordered_map<unsigned int, VBO_t> bufferObjects;
};

