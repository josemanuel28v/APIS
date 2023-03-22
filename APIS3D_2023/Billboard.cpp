#include "Billboard.h"
#include "System.h"

Billboard::Billboard(std::string mshFile)
{
	loadDataFromFile(mshFile.c_str());
}

void Billboard::computeModelMatrix()
{
	glm::mat4 model = System::getCamera()->getView();

	model[0][3] = position.x;
	model[1][3] = position.y;
	model[2][3] = position.z;
	model[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	model = glm::transpose(model);
	model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(this->scaling));

	this->setModelMt(model);
}
