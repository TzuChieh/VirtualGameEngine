#include "ShaderProgram.h"
#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Resource/ShaderProgramRes.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

#include <iostream>

DEFINE_LOG_SENDER(ShaderProgram);

using namespace ve;

void ShaderProgram::createProgram()
{
	ENGINE_LOG_IF(m_programResource != nullptr, ShaderProgram, LogLevel::NOTE_WARNING, 
	              "at createProgram(), program has already created");

	m_programResource = std::make_shared<ShaderProgramRes>();
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
	glUniform1i(m_programResource->getUniformId(uniformName), uniformValue);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Vector3f& vector3f) const
{
	glUniform3f(m_programResource->getUniformId(uniformName), vector3f.x, vector3f.y, vector3f.z);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Matrix4f& matrix4f) const
{
	glUniformMatrix4fv(m_programResource->getUniformId(uniformName), 1, GL_TRUE, &(matrix4f.m[0][0]));
}