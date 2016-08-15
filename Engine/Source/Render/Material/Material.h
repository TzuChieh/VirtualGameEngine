#pragma once

namespace xe
{

class ShaderProgram;

class Material
{
public:
	virtual ~Material() = 0;

	virtual void updateProgram(const ShaderProgram& shaderProgram) = 0;
};

}