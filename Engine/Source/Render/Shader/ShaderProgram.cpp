#include "ShaderProgram.h"
#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"
#include "ShaderProgramRes.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

#include <iostream>

DEFINE_LOG_SENDER(ShaderProgram);

using namespace ve;

ShaderProgram::ShaderProgram() : 
	m_programResource(nullptr)
{

}

ShaderProgram::ShaderProgram(const std::shared_ptr<ShaderProgramRes>& resource) : 
	m_programResource(resource)
{
	ENGINE_LOG_IF(m_programResource == nullptr, ShaderProgram, LogLevel::NOTE_WARNING,
	              "at ctor(), specified resource is null");
}

void ShaderProgram::completeProgram(const Shader& vertShader, const Shader& fragShader) const
{
	if(!m_programResource)
	{
		ENGINE_LOG(ShaderProgram, LogLevel::NOTE_WARNING, 
		           "at completeProgram(), program hasn't created yet, no action taken");
		return;
	}

	m_programResource->linkShaders(vertShader, fragShader);
	m_programResource->registerAllUniform();
}

void ShaderProgram::use() const
{
	m_programResource->bind();
}

void ShaderProgram::updateUniform(const std::string& uniformName, const int uniformValue) const
{
	m_programResource->updateUniformInt1(uniformName, uniformValue);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Vector3f& vector3f) const
{
	m_programResource->updateUniformFloat3(uniformName, vector3f.x, vector3f.y, vector3f.z);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Matrix4f& matrix4f) const
{
	m_programResource->updateUniformFloatMat4x4(uniformName, &(matrix4f.m[0][0]));
}