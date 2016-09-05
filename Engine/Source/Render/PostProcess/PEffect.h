#pragma once

#include "Render/Command/RenderCommand.h"

#include <vector>
#include <memory>

namespace ve
{

class ShaderProgramLibrary;
class GpuCommandQueue;

class PEffect
{

friend class PostProcessor;

public:
	virtual ~PEffect() = 0;

	virtual void create() = 0;

	// TODO: decompose

private:
	virtual void genRenderCommands(GpuCommandQueue* out_renderCommandQueue) const = 0;
};

}