#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Common/type.h"

#include <iostream>
#include <fstream>
#include <string>

#define SHADER_COMPILE_LOG_CHAR_LEN 2048

DEFINE_LOG_SENDER(Shader);

using namespace ve;

Shader::Shader(const std::string& fullFilename) : 
	m_shaderHandle(nullptr), 
	m_logger(LogSender("Shader <" + fullFilename + ">"))
{
	m_name = fullFilename;

	const uint32 dotIndex        = static_cast<uint32>(fullFilename.find_last_of('.'));
	const uint32 extensionLength = static_cast<uint32>(fullFilename.length() - dotIndex);
	const std::string& filenameExtension = fullFilename.substr(dotIndex, extensionLength);

	if(filenameExtension == ".vs")
	{
		m_type = VERTEX_SHADER;
	}
	else if(filenameExtension == ".gs")
	{
		m_type = GEOMETRY_SHADER;
	}
	else if(filenameExtension == ".fs")
	{
		m_type = FRAGMENT_SHADER;
	}
}

Shader::~Shader()
{
	if(m_shaderHandle.unique())
	{
		glDeleteShader(*m_shaderHandle);
		
		ENGINE_LOG(Shader, LogLevel::NOTE_MESSAGE, "ID <" + std::to_string(*m_shaderHandle) + "> deleted");
	}
}

void Shader::compile()
{
	if(m_shaderHandle)
	{
		ENGINE_LOG(Shader, LogLevel::NOTE_WARNING, 
		           "at compile(), ID <" + std::to_string(*m_shaderHandle) + "> already compiled, no action taken");
		return;
	}

	m_logger.log(LogLevel::NOTE_MESSAGE, "compiling");

	m_shaderHandle = std::make_shared<GLuint>(glCreateShader(m_type));

	std::string shaderSource = loadShaderSourceFromFile(m_name);
	const GLchar* shaderSourceChar = shaderSource.c_str();

	glShaderSource(*m_shaderHandle, 1, &shaderSourceChar, nullptr);
	glCompileShader(*m_shaderHandle);

	char compilerLog[SHADER_COMPILE_LOG_CHAR_LEN];
	glGetShaderInfoLog(*m_shaderHandle, SHADER_COMPILE_LOG_CHAR_LEN, nullptr, compilerLog);
	m_logger.log(LogLevel::NOTE_MESSAGE, "compiler log: \n" + std::string(compilerLog));

	GLint status;
	glGetShaderiv(*m_shaderHandle, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		m_logger.log(LogLevel::FATAL_ERROR, "compilation failed");
		exit(EXIT_FAILURE);
	}
}

std::string Shader::loadShaderSourceFromFile(const std::string& fullFilename)
{
	std::ifstream shaderFile;
	shaderFile.open(fullFilename, std::ios::in);

	std::string lineString;
	std::string sourceString;

	if(!shaderFile.is_open())
	{
		ENGINE_LOG(Shader, LogLevel::FATAL_ERROR, "failed to open file <" + fullFilename + ">");

		exit(EXIT_FAILURE);
	}
	else
	{
		while(shaderFile.good())
		{
			std::getline(shaderFile, lineString);
			sourceString.append(lineString + '\n');
		}

		shaderFile.close();
	}

	return sourceString;
}