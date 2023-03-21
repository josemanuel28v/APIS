#include "GLFWInputManager.h"


GLFWInputManager::GLFWInputManager()
{
    window = nullptr;
}

GLFWInputManager::~GLFWInputManager()
{
    if (window) delete window;

    window = nullptr;
}

void GLFWInputManager::init()
{
    // Poner todas las teclas a false
    unsigned int numKeys = sizeof(keybEvent) / sizeof(bool);
    for (int i = 0; i < numKeys; i++)
    {
        keybEvent[i] = false;
    }

    glfwSetKeyCallback(window, keyManager);
    glfwSetCursorPosCallback(window, mouseManager);
    glfwSetFramebufferSizeCallback(window, resizeManager);
    
    // Ocultar cursor y fijarlo en el centro de la pantalla
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPos(window, 0.0, 0.0);
}

void GLFWInputManager::keyManager(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Todas las keys que recoge son el mayúscula
    switch (action)
    {
    case GLFW_PRESS:
        keybEvent[key] = true;
        break;

    case GLFW_RELEASE:
        keybEvent[key] = false;
        break;
    }
}

void GLFWInputManager::mouseManager(GLFWwindow* window, double xpos, double ypos) 
{
    oldxpos = GLFWInputManager::xpos;
    oldypos = GLFWInputManager::ypos;
    GLFWInputManager::xpos = (int)xpos;
    GLFWInputManager::ypos = (int)ypos;
}

void GLFWInputManager::resizeManager(GLFWwindow* window, int width, int height)
{
    GLFWInputManager::width = width;
    GLFWInputManager::height = height;
    resized = true;
}
