#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "RenderProgram.h"
#include "GLSLShader.h"
#include "Texture.h"

class Material
{
public:

	enum NormalMode
	{
		NONE = 0,
		PER_VERTEX = 1,
		FROM_MAP = 2

	};

	enum BlendMode
	{
		SOLID, ALPHA, ADD, MUL
	};

	virtual ~Material();

	virtual void loadPrograms(std::vector<std::string> fileNames) = 0;
	virtual void prepare() = 0;
	virtual void prepareInstanced() = 0;

	virtual void setTexturing(bool texturing);
	virtual void setLighting(bool lighting);
	virtual void setCulling(bool culling);
	virtual void setDepthWrite(bool depthWrite);
	virtual void setBlendMode(BlendMode blendMode);
	virtual void setNormalMode(NormalMode normalMode);
	virtual void setTexture(Texture* colorMap);
	virtual void setProgram(RenderProgram* program);
	virtual void setColor(glm::vec4 color);
	virtual void setShininess(uint8_t shininess);

	virtual bool getTexturing() const;
	virtual bool getLighting() const;
	virtual bool getCulling() const;
	virtual bool getDepthWrite() const;
	virtual BlendMode getBlendMode() const;
	virtual NormalMode getNormalMode() const;
	virtual Texture* getTexture() const;
	virtual RenderProgram* getProgram() const;
	virtual glm::vec4 getColor() const;
	virtual uint8_t getShininess() const;

protected:

	RenderProgram* program = nullptr;
	Texture* colorMap = nullptr;
	Texture* normalMap = nullptr;

	glm::vec4 color = glm::vec4(1.0f);
	uint8_t shininess = 50;

	bool texturing = false;
	bool lighting = false;
	bool culling = false;
	bool depthWrite = false;
	NormalMode normalMode = NormalMode::NONE;
	BlendMode blendMode = BlendMode::SOLID;
};

