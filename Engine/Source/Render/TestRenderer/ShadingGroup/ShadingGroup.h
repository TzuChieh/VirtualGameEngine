#pragma once

#include "Render/Shader/ShaderProgram.h"

namespace ve
{

class ShadingGroup
{
public:
	virtual bool init(const ShaderProgram& shaderProgram) = 0;
};

}