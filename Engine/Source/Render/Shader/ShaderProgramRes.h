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

class ShaderProgramRes final
{
public:
	static void clearCachedBindingState();

public:
	ShaderProgramRes();
	~ShaderProgramRes();

	ShaderProgramRes& operator = (const ShaderProgramRes& rhs) = delete;

	void linkShaders(const Shader& vertShader, const Shader& fragShader) const;
	void bind() const;
	void registerAllUniforms();

	void updateUniformInt1(const std::string& uniformName, const int32 value) const;
	void updateUniformFloat3(const std::string& uniformName, const float32 x, const float32 y, const float32 z) const;
	void updateUniformFloatMat4x4(const std::string& uniformName, const float32* matrix4x4) const;

	GLuint getGlHandle() const;

private:
	GLuint m_programHandle;
	std::unordered_map<std::string, GLint> m_uniformIdMap;
	Logger m_logger;

	GLint getUniformIdFromOpenGL(const std::string& uniformName) const;
	GLint getUniformId(const std::string& uniformName) const;
	void registerUniform(const std::string& uniformName);

	void checkLinkStatus() const;
	void validatePorgram() const;

private:
	static GLuint bindedProgramHandle;

	static std::string getInfoLog(const GLuint programHandle);
};

}