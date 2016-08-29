#pragma once

#include "Common/logging.h"
#include "Render/Shader/ShaderProgram.h"

#include <string>
#include <unordered_map>

DECLARE_LOG_SENDER_EXTERN(ShaderProgramLibrary);

namespace ve
{

class ShaderProgramLibrary
{
public:
	const ShaderProgram& getShaderProgram(const std::string& fullFilename);

	void decompose();

private:
	std::unordered_map<std::string, ShaderProgram> m_shaderProgramNameMap;

	bool isShaderProgramLoaded(const std::string& fullFilename) const;
	const ShaderProgram& loadShaderProgram(const std::string& fullFilename);
};

}