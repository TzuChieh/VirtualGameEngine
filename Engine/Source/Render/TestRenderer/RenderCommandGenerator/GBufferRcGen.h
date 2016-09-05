#pragma once

#include "Render/Shader/ShaderProgram.h"
#include "Render/Command/RenderCommandSorter.h"
#include "Render/Command/RenderCommandInfo.h"
#include "Render/Command/GpuCommand.h"

#include <memory>
#include <vector>
#include <utility>

namespace ve
{

class StaticRenderableContainer;
class Camera;
class GpuCommandQueue;

class GBufferRcGen
{
public:
	GBufferRcGen();

	void renderGBuffer(const Camera& camera,
	                   const StaticRenderableContainer& renderables,
	                   GpuCommandQueue* out_commandQueue);

private:
	ShaderProgram m_gbufferShaderProgram;
	RenderCommandSorter m_commandSorter;
};

}