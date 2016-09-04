#pragma once

#include "Render/Command/RenderCommand.h"

#include <vector>
#include <memory>

namespace ve
{

class ShaderProgramLibrary;

class PEffect
{

friend class PostProcessor;

public:
	virtual ~PEffect() = 0;

	virtual void create() = 0;

	// TODO: decompose

private:
	virtual void genRenderCommands(std::vector<std::shared_ptr<RenderCommand>>* out_renderCommands) const = 0;
};

}