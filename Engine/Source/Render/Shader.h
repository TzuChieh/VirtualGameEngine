#pragma once

#include "Common/ThirdPartyLib/glew.h"

#include <string>

namespace xe
{

class Shader
{

friend class ShaderProgram;

public:
	Shader(const std::string& fullFilename);
	~Shader();

	void compile();

private:
	enum Type
	{
		VERTEX_SHADER   = GL_VERTEX_SHADER,
		GEOMETRY_SHADER = GL_GEOMETRY_SHADER,
		FRAGMENT_SHADER = GL_FRAGMENT_SHADER
	};

	std::string m_name;
	Type        m_type;
	GLuint      m_shaderId;

	static std::string loadShaderSourceFromFile(const std::string& fullFilename);
};

}