#pragma once

#include "ShadingGroup.h"

#include <vector>

namespace xe
{

class AbradedOpaqueSg : public ShadingGroup
{
public:
	virtual bool init(const ShaderProgram& shaderProgram) override;

private:
	ShaderProgram m_shaderProgram;
};

}