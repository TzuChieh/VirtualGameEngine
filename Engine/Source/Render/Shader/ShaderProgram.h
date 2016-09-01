#pragma once

#include "Common/Logger.h"

#include "Common/ThirdPartyLib/glew.h"

#include <string>
#include <unordered_map>
#include <memory>

DECLARE_LOG_SENDER_EXTERN(ShaderProgram);

namespace ve
{

class Shader;
class Vector3f;
class Matrix4f;
class ShaderProgramRes;
                                   
class ShaderProgram
{
public:
	ShaderProgram();
	ShaderProgram(const std::shared_ptr<ShaderProgramRes>& resource);

	void completeProgram(const Shader& vertShader, const Shader& fragShader) const;
	void use() const;

	void updateUniform(const std::string& uniformName, const int uniformValue) const;
	void updateUniform(const std::string& uniformName, const Vector3f& vector3f) const;
	void updateUniform(const std::string& uniformName, const Matrix4f& matrix4f) const;

	std::shared_ptr<ShaderProgramRes> getResource() const;

private:
	std::shared_ptr<ShaderProgramRes> m_programResource;
};

}