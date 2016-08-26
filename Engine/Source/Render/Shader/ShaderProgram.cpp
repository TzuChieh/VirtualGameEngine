#include "ShaderProgram.h"
#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

#include <iostream>

#define OPENGL_INVALID_UNIFORM_LOCATION -1

using namespace ve;

ShaderProgram::ShaderProgram() : 
	m_programHandle(nullptr),
	m_logger(LogSender("ShaderProgram"))
{
	
}

ShaderProgram::~ShaderProgram()
{
	if(m_programHandle.unique())
	{
		glDeleteProgram(*m_programHandle);

		std::cout << "ShaderProgram deleted" << std::endl;
	}
}

ShaderProgram& ShaderProgram::operator = (const ShaderProgram& rhs)
{
	if(m_programHandle.unique())
	{
		glDeleteProgram(*m_programHandle);

		std::cout << "ShaderProgram deleted" << std::endl;
	}

	m_programHandle = rhs.m_programHandle;
	m_uniformIdMap = rhs.m_uniformIdMap;

	return *this;
}

void ShaderProgram::createProgram()
{
	if(m_programHandle)
	{
		std::cerr << "ShaderProgram warning: at createProgram(), program has already created" << std::endl;
		return;
	}

	m_programHandle = std::make_shared<GLuint>(glCreateProgram());
}

void ShaderProgram::completeProgram(const Shader& vertShader, const Shader& fragShader) const
{
	// TODO: check errors

	if(!m_programHandle)
	{
		std::cerr << "ShaderProgram warning: at completeProgram(), program hasn't created yet" << std::endl;
		return;
	}

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

	// detect possible errors
	if(uniformLocationId == OPENGL_INVALID_UNIFORM_LOCATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR, "uniform name <" + uniformName + "> is invalid");
	}
	else if(uniformLocationId == GL_INVALID_VALUE)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR,
		             "ID <" + std::to_string(static_cast<uint32>(*m_programHandle)) + "> does not exist");
	}
	else if(uniformLocationId == GL_INVALID_OPERATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR, 
		             "ID <" + std::to_string(static_cast<uint32>(*m_programHandle)) + "> " + 
		             "is not a program object or the program has not been successfully linked");
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

		return OPENGL_INVALID_UNIFORM_LOCATION;
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