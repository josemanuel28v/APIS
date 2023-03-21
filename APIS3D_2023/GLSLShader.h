#pragma once
#define GLAD_ONLY_HEADERS
#include "common.h"
#include "RenderProgram.h"

class GLSLShader : public RenderProgram {
public:

    GLSLShader();

    virtual void setProgram(std::string programSrc, renderTypes_e type) override;
    virtual void linkPrograms() override;
    virtual std::string getErrorMsg(GLuint shaderID) override;
    virtual void use() override;

    virtual void setInt(std::string name, int value) override;
    virtual void setFloat(std::string name, float value) override;
    virtual void setVec3(std::string name, const glm::vec3& value) override;
    virtual void setVec4(std::string name, const glm::vec4& value) override;
    virtual void setMatrix(std::string name, const glm::mat4& value) override;
    virtual void setTexture2D(std::string loc, unsigned int textUnit) override;

private:
    std::string errorMSGs;
    std::map<renderTypes_e, unsigned int> shaders;

    GLint checkShaderError(GLuint shId);
    GLint checkProgramError();
    std::string readFile(const std::string fileName);
    void setupShaderVarList();
};

