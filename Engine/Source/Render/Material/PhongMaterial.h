#pragma once

#include "Material.h"

namespace xe
{

class PhongMaterial : public Material
{
public:
	virtual ~PhongMaterial() = 0;

	virtual const MaterialDefinition& getMaterialDefinition() const override;
	virtual void updateProgram(const ShaderProgram& shaderProgram) override;
};

}