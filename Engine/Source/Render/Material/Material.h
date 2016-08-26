#pragma once

namespace ve
{

class PbrOpaqueParamSet;

class Material
{
public:
	virtual ~Material() = 0;

	virtual bool populateMatlParamSet(PbrOpaqueParamSet* matlParamSet) const = 0;
};

}