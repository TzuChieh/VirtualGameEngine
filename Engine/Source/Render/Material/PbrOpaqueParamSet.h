#pragma once

#include "Common/type.h"
#include "MatlParamSet.h"

namespace ve
{

class PbrOpaqueParamSet : public MatlParamSet
{
public:
	PbrOpaqueParamSet();
	virtual ~PbrOpaqueParamSet() override;

	virtual void reset() override;

private:
	float32 m_roughness;
};

}