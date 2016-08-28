#pragma once

#include "Common/logging.h"
#include "Common/Logger.h"

#include "Common/ThirdPartyLib/glew.h"

#include <memory>
#include <string>
#include <unordered_map>

DECLARE_LOG_SENDER_EXTERN(ShaderProgramRes);

namespace ve
{

class Shader;

class ShaderProgramRes
{
public:
	ShaderProgramRes();
	~ShaderProgramRes();

	ShaderProgramRes& operator = (const ShaderProgramRes& rhs) = delete;

	void linkShaders(const Shader& vertShader, const Shader& fragShader) const;
	void bind() const;
	GLint getUniformId(const std::string& uniformName) const;
	void registerAllUniform();

private:
	GLuint m_programHandle;
	std::unordered_map<std::string, GLint> m_uniformIdMap;
	Logger m_logger;

	GLint getUniformIdFromOpenGL(const std::string& uniformName) const;
	void registerUniform(const std::string& uniformName);
};

}