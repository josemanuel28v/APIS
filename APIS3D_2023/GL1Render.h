#pragma once
#include "Render.h"

class GL1Render: public Render
{
public:
	/*Constructor que reciba por par�metros ancho/alto de la ventana*/
	GL1Render(int width, int height);
	virtual ~GL1Render();
	virtual void init() override;
	virtual void setupObject(Object* obj) override;
	virtual void removeObject(Object* obj) override;
	virtual void drawObject(Object* obj) override;
	virtual void drawObjects(std::vector<Object*>* objs) override;
	virtual bool isClosed() override;
	virtual int getWidth() override;
	virtual int getHeigth() override;
	virtual void setWidth(int width) override;
	virtual void setHeigth(int heigth) override;
	virtual void clearDisplay() override;
	virtual void swapBuffers() override;

	virtual void setupObjectInstanced(Object* obj, unsigned numInstances) override {};
	virtual void drawObjectInstanced(Object* obj, unsigned numInstances, glm::mat4* mvps, glm::vec4* colors) override {};

	// Duda: Necesario para inicializar el glfwSetKeyCallback en glfwInput
	virtual GLFWwindow* getWindow() { return window; }

protected:
	//ATRIBUTOS: Puntero a una ventana de glfw 
	GLFWwindow* window = nullptr;
};

