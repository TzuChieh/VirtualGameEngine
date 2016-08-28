#pragma once

#include "Common/logging.h"
#include "ShaderProgram.h"

#include <string>
#include <unordered_map>

DECLARE_LOG_SENDER_EXTERN(ShaderProgramLibrary);

namespace ve
{

class ShaderProgramLibrary
{
public:
	//static const ShaderProgram& getShaderProgram(const std::string& shaderProgramName);

private:
	static std::unordered_map<std::string, ShaderProgram> shaderProgramNameMap;

	static bool isShaderProgramLoaded(const std::string& shaderProgramName);
};

}