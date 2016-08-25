#pragma once

#include "Render/Shader/ShaderProgram.h"

#include <vector>
#include <memory>

namespace xe
{

class RenderCommand;
class StaticRenderableContainer;
class Camera;

class TestRcGen
{
public:
	bool init(const ShaderProgram& shaderProgram);

	void genRenderCommands(const Camera& camera,
	                       const StaticRenderableContainer& renderables,
	                       std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const;

private:
	ShaderProgram m_shaderProgram;
};

}