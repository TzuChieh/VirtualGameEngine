#include "ShaderProgramLibrary.h"

DEFINE_LOG_SENDER(ShaderProgramLibrary);

using namespace ve;

std::unordered_map<std::string, ShaderProgram> ShaderProgramLibrary::shaderProgramNameMap;

//const ShaderProgram& ShaderProgramLibrary::getShaderProgram(const std::string& shaderProgramName)
//{
//
//}

bool ShaderProgramLibrary::isShaderProgramLoaded(const std::string& shaderProgramName)
{
	//ENGINE_LOG_IF(ShaderProgramLibrary,);

	return shaderProgramNameMap.count(shaderProgramName) == 1;
}