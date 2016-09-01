#pragma once

#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Shader/ShaderProgram.h"

#include <memory>
#include <vector>

namespace ve
{

class StaticRenderableContainer;
class Camera;

class GBufferRcGen
{
public:
	GBufferRcGen();

	void genRenderCommands(const Camera& camera,
	                       const StaticRenderableContainer& renderables,
		                   std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const;

private:
	ShaderProgram m_gbufferShaderProgram;
};

}