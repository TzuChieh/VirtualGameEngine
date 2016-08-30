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
	// TODO: verify Shader state (compiled or not... etc.)

	m_logger.log(LogLevel::NOTE_MESSAGE, "linking <" + vertShader.m_name + "> and <" + fragShader.m_name + ">");

	glAttachShader(m_programHandle, *(vertShader.m_shaderHandle));
	glAttachShader(m_programHandle, *(fragShader.m_shaderHandle));

	glLinkProgram(m_programHandle);

	glDetachShader(m_programHandle, *(vertShader.m_shaderHandle));
	glDetachShader(m_programHandle, *(fragShader.m_shaderHandle));

	checkLinkStatus();
	validatePorgram();
}

void ShaderProgramRes::bind() const
{
	glUseProgram(m_programHandle);
}

void ShaderProgramRes::registerAllUniform()
{
	GLint size;  // size of the uniform
	GLenum type; // type of the uniform (float, vec3 or mat4, etc.)

	const GLsizei arrSize = 256; // maximum uniform name length
	GLchar uniformName[arrSize]; // uniform name in GLSL
	GLsizei uniformNameLength;   // actual uniform name length

	GLint numActiveUniforms;
	glGetProgramiv(m_programHandle, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

	for(GLint i = 0; i < numActiveUniforms; i++)
	{
		glGetActiveUniform(m_programHandle, i, arrSize, &uniformNameLength, &size, &type, uniformName);

		registerUniform(std::string(uniformName));
	}
}

void ShaderProgramRes::registerUniform(const std::string& uniformName)
{
	m_uniformIdMap.emplace(uniformName, getUniformIdFromOpenGL(uniformName));

	ENGINE_LOG(ShaderProgramRes, LogLevel::DEBUG_MAX, 
	           "program <" + std::to_string(m_programHandle) + "> uniform <" + uniformName + "> registered");
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

GLint ShaderProgramRes::getUniformId(const std::string& uniformName) const
{
	if(m_uniformIdMap.count(uniformName) == 1)
	{
		return m_uniformIdMap.at(uniformName);
	}

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) == 0,
	              ShaderProgramRes, LogLevel::NOTE_WARNING,
	              "uniform name <" + uniformName + "> does not exist");

	ENGINE_LOG_IF(m_uniformIdMap.count(uniformName) != 0,
	              ShaderProgramRes, LogLevel::NOTE_WARNING,
	              "uniform name <" + uniformName + "> cause unordered_map.count() > 1");

	return OPENGL_INVALID_UNIFORM_LOCATION;
}

void ShaderProgramRes::checkLinkStatus() const
{
	GLint isLinked = 0;
	glGetProgramiv(m_programHandle, GL_LINK_STATUS, &isLinked);
	if(isLinked == GL_FALSE)
	{
		m_logger.log(LogLevel::FATAL_ERROR, "link failed, log: " + ShaderProgramRes::getInfoLog(m_programHandle));
	}
}

void ShaderProgramRes::validatePorgram() const
{
	glValidateProgram(m_programHandle);

	GLint isValidated = 0;
	glGetProgramiv(m_programHandle, GL_VALIDATE_STATUS, &isValidated);
	if(isValidated == GL_FALSE)
	{
		m_logger.log(LogLevel::FATAL_ERROR, "validation failed, log: " + ShaderProgramRes::getInfoLog(m_programHandle));
	}
}

std::string ShaderProgramRes::getInfoLog(const GLuint programHandle)
{
	GLint infoLogLength = 0;
	glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH, &infoLogLength);

	// maxLength includes the NULL character \0
	std::vector<GLchar> infoLog(infoLogLength);
	glGetProgramInfoLog(programHandle, infoLogLength, &infoLogLength, infoLog.data());

	return std::string(infoLog.data());
}