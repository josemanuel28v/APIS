#pragma once

#define GLAD_ONLY_HEADERS
#include "common.h"
#include "MSH.h"

class State
{
	inline static std::unordered_map<std::string, MSH*> loadedMSH;

public:
	static void addMSH(std::string id, MSH* msh);
	static bool existMSH(std::string id);
	static MSH* getMSH(std::string id);
	static void showMSH();
};

