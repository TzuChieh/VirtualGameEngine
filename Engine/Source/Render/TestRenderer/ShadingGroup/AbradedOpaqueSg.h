#pragma once

#include "ShadingGroup.h"

#include <vector>

namespace ve
{

class AbradedOpaqueSg : public ShadingGroup
{
public:
	virtual bool init(const ShaderProgram& shaderProgram) override;

private:
	ShaderProgram m_shaderProgram;
};

}