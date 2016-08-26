#include "Shader.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Common/type.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace ve;

Shader::Shader(const std::string& fullFilename)
{
	m_name = fullFilename;

	const int32 dotIndex        = (int32)fullFilename.find_last_of('.');
	const int32 extensionLength = (int32)fullFilename.length() - dotIndex;
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
		
		std::cout << "Shader deleted" << std::endl;
	}
}

void Shader::compile()
{
	if(m_shaderHandle)
	{
		std::cerr << "Shader Warning: shader has already compiled, no action taken" << std::endl;
		return;
	}

	m_shaderHandle = std::make_shared<GLuint>(glCreateShader(m_type));

	std::string shaderSource = loadShaderSourceFromFile(m_name);
	const GLchar* shaderSourceChar = shaderSource.c_str();

	glShaderSource(*m_shaderHandle, 1, &shaderSourceChar, nullptr);
	glCompileShader(*m_shaderHandle);

	char compileLog[2048];
	glGetShaderInfoLog(*m_shaderHandle, 2048, nullptr, compileLog);

	std::cout << "Shader <" << m_name << "> compile log" << std::endl;
	std::cout << compileLog << std::endl;

	GLint status;
	glGetShaderiv(*m_shaderHandle, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE)
	{
		std::cout << "shader compilation failed" << std::endl;
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
		std::cerr << "Shader Error: failed to open file <" + fullFilename + ">";
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