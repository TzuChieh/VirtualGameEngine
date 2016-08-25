#pragma once

#include "Common/ThirdPartyLib/glew.h"

#include <string>
#include <unordered_map>
#include <memory>

namespace xe
{

class Shader;
class Vector3f;
class Matrix4f;

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	ShaderProgram& operator = (const ShaderProgram& rhs);

	void createProgram();
	void completeProgram(const Shader& vertShader, const Shader& fragShader) const;
	void use() const;
	void registerUniform(const std::string& uniformName);

	void updateUniform(const std::string& uniformName, const int uniformValue);
	void updateUniform(const std::string& uniformName, const Vector3f& vector3f);
	void updateUniform(const std::string& uniformName, const Matrix4f& matrix4f);

private:
	std::shared_ptr<GLuint> m_programHandle;
	std::unordered_map<std::string, GLint> m_uniformIdMap;

	GLint getUniformIdFromOpenGL(const std::string& uniformName) const;
	GLint getUniformId(const std::string& uniformName);
};

}