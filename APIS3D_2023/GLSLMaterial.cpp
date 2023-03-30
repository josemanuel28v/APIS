#include "GLSLMaterial.h"
#include "GLTexture.h"
#include "System.h"

using renderType = RenderProgram::renderTypes_e;

GLSLMaterial::GLSLMaterial()
{
	this->program = new GLSLShader();
	this->colorMap = nullptr;
	this->normalMap = nullptr;
	color = glm::vec4(1.0, 1.0, 1.0, 1.0);
}

void GLSLMaterial::loadPrograms(std::vector<std::string> fileNames)
{
	for (const auto& file : fileNames) 
	{
		if (file.ends_with("vertex"))
		{
			this->program->setProgram(file, renderType::vertex);
		}
		else if (file.ends_with("fragment"))
		{
			this->program->setProgram(file, renderType::fragment);
		}
	}

	this->program->linkPrograms();
}

void GLSLMaterial::prepare()
{
	program->use();

	if (texturing)
	{
		Texture::TextureType textType = colorMap->getType();

		program->setInt("textType", (int)textType);

		switch (textType)
		{
		case Texture::COLOR2D:
			colorMap->bind(0);
			glDisable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
			program->setTexture2D("colorText", 0);
			program->setTexture2D("cubeText", 1);
			program->setTexture2D("reflectText", 2);
			program->setTexture2D("refractText", 3);
			program->setTexture2D("normalText", 4);
			break;

		case Texture::COLOR3D:
			colorMap->bind(1);
			glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
			program->setTexture2D("colorText", 0);
			program->setTexture2D("cubeText", 1);
			program->setTexture2D("reflectText", 2);
			program->setTexture2D("refractText", 3);
			program->setTexture2D("normalText", 4);
			break;

			/*
				Necesario setear colorText y cubeText en ambos casos
			*/
		}
	}

	if (reflection)
	{
		reflectionMap->bind(2);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		program->setTexture2D("colorText", 0);
		program->setTexture2D("cubeText", 1);
		program->setTexture2D("reflectText", 2);
		program->setTexture2D("refractText", 3);
		program->setTexture2D("normalText", 4);

	}

	if (refraction)
	{
		refractionMap->bind(3);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
		program->setTexture2D("colorText", 0);
		program->setTexture2D("cubeText", 1);
		program->setTexture2D("reflectText", 2);
		program->setTexture2D("refractText", 3);
		program->setTexture2D("normalText", 4);
	}

	if (normalMapping)
	{
		normalMap->bind(4);
		program->setTexture2D("colorText", 0);
		program->setTexture2D("cubeText", 1);
		program->setTexture2D("reflectText", 2);
		program->setTexture2D("refractText", 3);
		program->setTexture2D("normalText", 4);
	}

	// Uniforms
	program->setMatrix("model", System::getModelMatrix());
	program->setMatrix("view", System::getCamera()->getView());
	program->setMatrix("proj", System::getCamera()->getProjection());
	program->setVec3("eyePos", System::getCamera()->getPosition());
	program->setVec3("ambient", System::getAmbient());
	program->setInt("texturing", (int)texturing);
	program->setInt("lighting", (int)lighting);
	program->setInt("normalMapping", (int)normalMapping);
	program->setInt("shininess", shininess);
	program->setVec4("baseColor", color);
	program->setInt("numLights", System::lights->size());
	program->setInt("computeReflect", (int)reflection);
	program->setInt("computeRefract", (int)refraction);
	program->setFloat("refractCoef", refractCoef);

	for (int i = 0; i < System::lights->size(); i++)
	{
		program->setVec3("lights[" + std::to_string(i) + "].position", (*System::lights)[i]->getPosition());
		program->setVec3("lights[" + std::to_string(i) + "].color", (*System::lights)[i]->getInfo().color);
		program->setInt("lights[" + std::to_string(i) + "].type", (int)(*System::lights)[i]->getInfo().type);
		program->setFloat("lights[" + std::to_string(i) + "].intensity", (int)(*System::lights)[i]->getInfo().intensity);
		program->setFloat("lights[" + std::to_string(i) + "].linearAtt", (int)(*System::lights)[i]->getInfo().linearAtt);
	}

	// Depth test
	depthWrite ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);

	// Culling test
	if (culling) 
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else 
	{
		glDisable(GL_CULL_FACE);
	}

	// Modo de mezclado de colores
	switch (blendMode)
	{	
	case SOLID:
		glBlendFunc(GL_ONE, GL_ZERO);
		break;
	case ALPHA: 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	
	case MUL: 
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;
	
	case ADD: 
		glBlendFunc(GL_ONE, GL_ONE);
		break;
	}
}

void GLSLMaterial::prepareInstanced()
{
	program->use();

	if (getTexturing())
	{
		colorMap->bind(0);
		program->setTexture2D("colorText", 0);
	}
	program->setInt("texturing", (int)texturing);

	// Depth test
	depthWrite ? glDepthMask(GL_TRUE) : glDepthMask(GL_FALSE);

	// Culling test
	if (culling)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	// Modo de mezclado de colores
	switch (blendMode)
	{
	case SOLID:
		glBlendFunc(GL_ONE, GL_ZERO);
		break;

	case ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;

	case MUL:
		glBlendFunc(GL_DST_COLOR, GL_ZERO);
		break;

	case ADD:
		glBlendFunc(GL_ONE, GL_ONE);
		break;
	}
}


