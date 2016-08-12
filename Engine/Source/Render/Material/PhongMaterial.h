#pragma once

#include "Common/type.h"
#include "Material.h"

namespace xe
{

class PhongMaterial : public Material
{
public:
	PhongMaterial();
	virtual ~PhongMaterial() = 0;

	virtual const MaterialDefinition& getMaterialDefinition() const override;
	virtual void updateProgram(const ShaderProgram& shaderProgram) override;

private:
	float32 m_exponent;
};

}