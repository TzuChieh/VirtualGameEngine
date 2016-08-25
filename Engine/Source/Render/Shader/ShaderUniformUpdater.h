#pragma once

namespace xe
{

class ShaderProgram;

class ShaderUniformUpdater
{
public:
	virtual ~ShaderUniformUpdater() = 0;

	virtual void updateUniforms(ShaderProgram& shaderProgram) const = 0;
};

}