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
	void createProgram();
	void completeProgram(const Shader& vertShader, const Shader& fragShader) const;
	void use() const;
	void registerUniform(const std::string& uniformName);

	void updateUniform(const std::string& uniformName, const int uniformValue);
	void updateUniform(const std::string& uniformName, const Vector3f& vector3f);
	void updateUniform(const std::string& uniformName, const Matrix4f& matrix4f);

private:
	std::shared_ptr<ShaderProgramRes> m_programResource;
};

}