#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "RenderProgram.h"
#include "GLSLShader.h"
#include "Texture.h"

class Material
{

public:

	enum normalType {
		vertexNormal = 1, normalTexture = 2, none = 0
	};

	virtual ~Material();
	virtual void loadPrograms(std::vector<std::string> fileNames) = 0;
	virtual void prepare() = 0;
	virtual void setIsTextured(bool isTextured);
	virtual bool getIsTextured();
	virtual Texture* getTexture();
	virtual void setTexture(Texture* texture);
	virtual normalType getNormalType();
	virtual void setNormalType(normalType type);
	virtual void setProgram(RenderProgram*);
	virtual RenderProgram* getProgram();
	const glm::vec4& getColor() const;
	void setColor(const glm::vec4& color);
	uint8_t getShininess() const;
	void setShininess(uint8_t shininess);


protected:
	RenderProgram* program = nullptr;
	Texture* colorTexture = nullptr;
	Texture* normalMap = nullptr;
	glm::vec4 color = glm::vec4(1.0f);
	uint8_t shininess = 50;
	bool isTextured = false;
	normalType normType = normalType::none;

};

