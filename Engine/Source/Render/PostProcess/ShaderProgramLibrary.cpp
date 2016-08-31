#include "ShaderProgramLibrary.h"
#include "Render/Shader/Shader.h"
#include "Render/Shader/ShaderProgramRes.h"

#include <memory>

DEFINE_LOG_SENDER(ShaderProgramLibrary);

using namespace ve;

// TODO: or get by a ShaderDirectories (for combined compute shader or geometry shader)?
// or even a custom file format combining vs fs gs cs...
const ShaderProgram& ShaderProgramLibrary::getShaderProgram(const std::string& fullFilename)
{
	if(isShaderProgramLoaded(fullFilename))
	{
		return m_shaderProgramNameMap.at(fullFilename);
	}
	else
	{
		return loadShaderProgram(fullFilename);
	}
}

void ShaderProgramLibrary::decompose()
{
	m_shaderProgramNameMap.clear();
}

bool ShaderProgramLibrary::isShaderProgramLoaded(const std::string& fullFilename) const
{
	ENGINE_LOG_IF(m_shaderProgramNameMap.count(fullFilename) > 1,
	              ShaderProgramLibrary, LogLevel::DEBUG_MAX, "unordered_map.count() > 1");

	return m_shaderProgramNameMap.count(fullFilename) == 1;
}

const ShaderProgram& ShaderProgramLibrary::loadShaderProgram(const std::string& fullFilename)
{
	// TODO: check file existence

	ShaderProgram shaderProgram(std::make_shared<ShaderProgramRes>());

	Shader vertShader(fullFilename + ".vs");
	Shader fragShader(fullFilename + ".fs");
	vertShader.compile();
	fragShader.compile();


	shaderProgram.completeProgram(vertShader, fragShader);

	m_shaderProgramNameMap.emplace(fullFilename, shaderProgram);

	return shaderProgram;
}