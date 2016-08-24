#pragma once

#include "Render/Shader/ShaderProgram.h"

#include <vector>

namespace xe
{

class StaticRenderable;
class RenderCommand;

class TestRcGen
{
public:
	TestRcGen(const ShaderProgram& shaderProgram);

	/*void genRenderCommands(const std::vector<StaticRenderable>& renderables, 
	                       std::vector<RenderCommand>* out_renderCommands) const;*/

private:
	ShaderProgram m_shaderProgram;
};

}