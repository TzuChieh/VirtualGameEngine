#pragma once

namespace xe
{

class MaterialDefinition;
class ShaderProgram;

class Material
{
public:
	virtual ~Material() = 0;

	virtual const MaterialDefinition& getMaterialDefinition() const = 0;
	virtual void updateProgram(const ShaderProgram& shaderProgram) = 0;
};

}