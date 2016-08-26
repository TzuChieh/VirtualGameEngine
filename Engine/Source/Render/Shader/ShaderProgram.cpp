#include "ShaderProgram.h"
#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"

#include "Math/Vector3f.h"
#include "Math/Matrix4f.h"

#include <iostream>

#define OPENGL_INVALID_UNIFORM_LOCATION -1

DEFINE_LOG_SENDER(ShaderProgram);

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
	if(!m_programHandle)
	{
		std::cerr << "ShaderProgram warning: at completeProgram(), program hasn't created yet" << std::endl;
		return;
	}

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

	// detect possible errors
	if(uniformLocationId == OPENGL_INVALID_UNIFORM_LOCATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR, "uniform name <" + uniformName + "> is invalid");
	}
	else if(uniformLocationId == GL_INVALID_VALUE)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR,
		             "ID <" + std::to_string(*m_programHandle) + "> does not exist");
	}
	else if(uniformLocationId == GL_INVALID_OPERATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR, 
		             "ID <" + std::to_string(*m_programHandle) + "> " + 
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

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) == 0, 
	              ShaderProgram, LogLevel::NOTE_WARNING, 
	              "uniform name <" + uniformName + "> does not exist");

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) != 0,
	              ShaderProgram, LogLevel::NOTE_WARNING,
	              "uniform name <" + uniformName + "> cause unordered_map.count() > 1");

	return OPENGL_INVALID_UNIFORM_LOCATION;
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