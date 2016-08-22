#include "ShaderProgram.h"
#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

#include <iostream>

using namespace xe;

ShaderProgram::ShaderProgram()
{
	m_programHandle = std::make_shared<GLuint>(glCreateProgram());
}

ShaderProgram::~ShaderProgram()
{
	if(m_programHandle.unique())
	{
		glDeleteProgram(*m_programHandle);

		std::cout << "ShaderProgram deleted" << std::endl;
	}
}

void ShaderProgram::completeProgram(const Shader& vertShader, const Shader& fragShader) const
{
	// TODO: check errors

	glAttachShader(*m_programHandle, *(vertShader.m_shaderHandle));
	glAttachShader(*m_programHandle, *(fragShader.m_shaderHandle));

	glLinkProgram(*m_programHandle);

	glDetachShader(*m_programHandle, *(vertShader.m_shaderHandle));
	glDetachShader(*m_programHandle, *(fragShader.m_shaderHandle));
}

void ShaderProgram::use() const
{
	glUseProgram(*m_programHandle);
}

void ShaderProgram::registerUniform(const std::string& uniformName)
{
	m_uniformIdMap.emplace(uniformName, getUniformIdFromOpenGL(uniformName));
}

GLint ShaderProgram::getUniformIdFromOpenGL(const std::string& uniformName) const
{
	int uniformLocationId = glGetUniformLocation(*m_programHandle, uniformName.c_str());

	if(uniformLocationId == 0xFFFFFFFF)
	{
		std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> does not exist \n";
	}

	return uniformLocationId;
}

GLint ShaderProgram::getUniformId(const std::string& uniformName)
{
	if(m_uniformIdMap.count(uniformName) == 1)
	{
		return m_uniformIdMap[uniformName];
	}
	else
	{
		if(m_uniformIdMap.count(uniformName) == 0)
		{
			std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> does not exist \n";
		}
		else
		{
			std::cerr << "ShaderPorgram Error: uniform <" + uniformName + "> caused unknown behavior, "
			          << "unordered_map.count() returns value larger than 1 \n";
		}

		return 0xFFFFFFFF;
	}
}

void ShaderProgram::updateUniform(const std::string& uniformName, const int uniformValue)
{
	glUniform1i(getUniformId(uniformName), uniformValue);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Vector3f& vector3f)
{
	glUniform3f(getUniformId(uniformName), vector3f.x, vector3f.y, vector3f.z);
}

void ShaderProgram::updateUniform(const std::string& uniformName, const Matrix4f& matrix4f)
{
	glUniformMatrix4fv(getUniformId(uniformName), 1, GL_TRUE, &(matrix4f.m[0][0]));
}