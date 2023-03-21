#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"

class InputManager
{
public:

	virtual void init() = 0;
	virtual bool isPressed(int key);
	virtual glm::ivec2 getMousePosition();
	virtual glm::ivec2 getOldMousePosition();

	virtual glm::ivec2 getWindowSize() { return glm::ivec2(width, height); }
	virtual bool isWindowResized() { return resized; }
	virtual void setWindowResized() { resized = false; }

protected:
	inline static bool keybEvent[512];
	inline static int xpos, ypos, oldxpos, oldypos = 0;
	inline static int width, height;
	inline static bool resized = false;
};

