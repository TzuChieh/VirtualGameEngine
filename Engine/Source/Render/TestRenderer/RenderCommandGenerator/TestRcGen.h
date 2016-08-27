#pragma once

#include "Render/Shader/ShaderProgram.h"

#include <vector>
#include <memory>

namespace ve
{

class RenderCommand;
class StaticRenderableContainer;
class Camera;

class TestRcGen
{
public:
	bool init();

	void genRenderCommands(const Camera& camera,
	                       const StaticRenderableContainer& renderables,
	                       std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const;

private:
	ShaderProgram m_shaderProgram;
};

}