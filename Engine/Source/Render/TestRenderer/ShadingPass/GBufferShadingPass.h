#pragma once

#include "Render/Shader/ShaderProgram.h"
#include "Render/Command/RenderCommandSorter.h"
#include "Render/Command/RenderCommandInfo.h"
#include "Render/Command/GpuCommand.h"

namespace ve
{

class GpuCommandQueue;

class GBufferShadingPass
{
public:

	void genRenderCommands(GpuCommandQueue* out_renderCommandQueue) const;

private:
};

}