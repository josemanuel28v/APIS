#pragma once
#include "Object.h"

class Render
{
public:

	Render(int width, int height) : width(width), height(height) {}

	virtual void init() = 0;
	virtual void setupObject(Object* obj) = 0;
	virtual void removeObject(Object* obj) = 0;
	virtual void drawObjects(std::vector<Object*>* objs) = 0;

	virtual int getWidth() = 0;
	virtual int getHeigth() = 0;

	virtual void setWidth(int width) = 0;
	virtual void setHeigth(int heigth) = 0;

	virtual bool isClosed() = 0;

protected:
	int width;
	int height;
};

