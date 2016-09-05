#pragma once

#include "Render/Framebuffer.h"
#include "Core/EngineProxy.h"

#include <vector>
#include <memory>

namespace ve
{

class PEffect;
class Texture2D;
class RenderCommand;
class GpuCommandQueue;

class PostProcessor
{
public:
	bool init(const EngineProxy& engineProxy);
	void decompose();

	void renderEffectToTexture(const PEffect& effect, const Texture2D& destination);
	void renderEffectToDisplay(const PEffect& effect, GpuCommandQueue* out_gpuCommandQueue);

private:
	Framebuffer m_framebuffer;
	std::vector<std::shared_ptr<RenderCommand>> m_renderCommands;
	EngineProxy m_engineProxy;

	/*void populateCommandBuffer(const PEffect& effect);
	void executeCommands();*/
};

}