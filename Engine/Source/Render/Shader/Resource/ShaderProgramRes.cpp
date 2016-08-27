#include "ShaderProgramRes.h"
#include "Render/Shader/Shader.h"

#define OPENGL_INVALID_UNIFORM_LOCATION -1

DEFINE_LOG_SENDER(ShaderProgramRes);

using namespace ve;

ShaderProgramRes::ShaderProgramRes()
{
	m_programHandle = glCreateProgram();

	m_logger.setLogSender(LogSender("ShaderProgramRes ID <" + std::to_string(m_programHandle) + ">"));
}

ShaderProgramRes::~ShaderProgramRes()
{
	glDeleteProgram(m_programHandle);

	m_logger.log(LogLevel::NOTE_MESSAGE, "deleted");
}

void ShaderProgramRes::linkShaders(const Shader& vertShader, const Shader& fragShader) const
{
	// TODO: check errors

	m_logger.log(LogLevel::NOTE_MESSAGE, "linking <" + vertShader.m_name + "> and <" + fragShader.m_name + ">");

	glAttachShader(m_programHandle, *(vertShader.m_shaderHandle));
	glAttachShader(m_programHandle, *(fragShader.m_shaderHandle));

	glLinkProgram(m_programHandle);

	glDetachShader(m_programHandle, *(vertShader.m_shaderHandle));
	glDetachShader(m_programHandle, *(fragShader.m_shaderHandle));
}

void ShaderProgramRes::bind() const
{
	glUseProgram(m_programHandle);
}

void ShaderProgramRes::registerUniform(const std::string& uniformName)
{
	m_uniformIdMap.emplace(uniformName, getUniformIdFromOpenGL(uniformName));
}

GLint ShaderProgramRes::getUniformIdFromOpenGL(const std::string& uniformName) const
{
	int uniformLocationId = glGetUniformLocation(m_programHandle, uniformName.c_str());

	// detect possible errors
	if(uniformLocationId == OPENGL_INVALID_UNIFORM_LOCATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR, "uniform name <" + uniformName + "> is invalid");
	}
	else if(uniformLocationId == GL_INVALID_VALUE)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR,
		             "ID <" + std::to_string(m_programHandle) + "> does not exist");
	}
	else if(uniformLocationId == GL_INVALID_OPERATION)
	{
		m_logger.log(LogLevel::RECOVERABLE_ERROR,
		             "ID <" + std::to_string(m_programHandle) + "> " +
		             "is not a program object or the program has not been successfully linked");
	}

	return uniformLocationId;
}

GLint ShaderProgramRes::getUniformId(const std::string& uniformName)
{
	if(m_uniformIdMap.count(uniformName) == 1)
	{
		return m_uniformIdMap[uniformName];
	}

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) == 0,
	              ShaderProgramRes, LogLevel::NOTE_WARNING,
	              "uniform name <" + uniformName + "> does not exist");

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) != 0,
	              ShaderProgramRes, LogLevel::NOTE_WARNING,
	              "uniform name <" + uniformName + "> cause unordered_map.count() > 1");

	return OPENGL_INVALID_UNIFORM_LOCATION;
}