#pragma once

#include "Core/GraphicsApi.h"

#include <string>
#include <unordered_map>

namespace xe {

class Shader;

class ShaderProgram {
	public:
		ShaderProgram();
		~ShaderProgram();

		void completeProgram(Shader& vertShader, Shader& fragShader) const;
		void use() const;
		void registerUniform(const std::string& uniformName);
		void updateUniform(const std::string& uniformName, const int uniformValue);

	private:
		GLuint m_programId;
		std::unordered_map<std::string, GLint> m_uniformIdMap;

		GLint getUniformIdFromOpenGL(const std::string& uniformName) const;
		GLint getUniformId(const std::string& uniformName);
	};

}