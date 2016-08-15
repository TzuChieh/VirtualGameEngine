#pragma once

#include "Common/type.h"
#include "Material.h"

namespace xe
{

class AbradedOpaqueMaterial : public Material
{
public:
	AbradedOpaqueMaterial();
	virtual ~AbradedOpaqueMaterial() = 0;
	
	virtual void updateProgram(const ShaderProgram& shaderProgram) override;

private:
	float32 m_roughness;
};

}