#include "PostProcessor.h"
#include "PEffect.h"
#include "Render/Command/RenderCommand.h"
#include "Render/Framebuffer.h"
#include "Render/FramebufferRes.h"
#include "Render/Command/GpuCommandQueue.h"

using namespace ve;

bool PostProcessor::init(const EngineProxy& engineProxy)
{
	m_engineProxy = engineProxy;

	m_framebuffer = Framebuffer(std::make_shared<FramebufferRes>(engineProxy.getDisplayWidthPx(), engineProxy.getDisplayHeightPx()));

	return true;
}

void PostProcessor::decompose()
{
	
}

void PostProcessor::renderEffectToTexture(const PEffect& effect, const Texture2D& destination)
{
	m_framebuffer.attachRenderTarget(destination, 0, ETargetSlot::COLOR_0);
	m_framebuffer.setRenderDimensionPx(destination.getWidthPx(), destination.getHeightPx());
	m_framebuffer.useForRendering();

	/*populateCommandBuffer(effect);
	executeCommands();*/
}

void PostProcessor::renderEffectToDisplay(const PEffect& effect, GpuCommandQueue* out_gpuCommandQueue)
{
	Framebuffer::bindDefaultForRendering(m_engineProxy.getDisplayWidthPx(), m_engineProxy.getDisplayHeightPx());

	effect.genRenderCommands(out_gpuCommandQueue);

	/*populateCommandBuffer(effect);
	executeCommands();*/
}

//void PostProcessor::populateCommandBuffer(const PEffect& effect)
//{
//	m_renderCommands.clear();
//	effect.genRenderCommands(&m_renderCommands);
//}
//
//void PostProcessor::executeCommands()
//{
//	for(auto& renderCommand : m_renderCommands)
//	{
//		renderCommand->execute();
//	}
//}