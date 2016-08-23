#pragma once

#include "Render/ShaderProgram.h"

namespace xe
{

class ShadingGroup
{
public:
	virtual bool init(const ShaderProgram& shaderProgram) = 0;
};

}