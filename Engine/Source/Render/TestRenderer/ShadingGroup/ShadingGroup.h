#pragma once

#include "Render/Shader/ShaderProgram.h"

namespace xe
{

class ShadingGroup
{
public:
	virtual bool init(const ShaderProgram& shaderProgram) = 0;
};

}