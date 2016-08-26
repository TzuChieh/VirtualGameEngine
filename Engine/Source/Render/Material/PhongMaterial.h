#pragma once

#include "Common/type.h"
#include "Material.h"

namespace ve
{

class PhongMaterial : public Material
{
public:
	PhongMaterial();
	virtual ~PhongMaterial() override;

	virtual bool populateMatlParamSet(PbrOpaqueParamSet* matlParamSet) const override;
	
private:
	float32 m_kd;
	float32 m_ks;
	uint32 m_shininess;
};

}