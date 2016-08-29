#include "PostProcessor.h"
#include "PEffect.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Framebuffer.h"

using namespace ve;

bool PostProcessor::init(const EngineProxy& engineProxy)
{
	m_engineProxy = engineProxy;

	m_framebuffer.create();

	return true;
}

void PostProcessor::decompose()
{
	
}

void PostProcessor::renderEffectToTexture(const PEffect& effect, const Texture2D& destination)
{
	m_framebuffer.attachRenderTarget(destination, ETargetSlot::COLOR_0);
	m_framebuffer.setRenderDimensionPx(destination.getWidthPx(), destination.getHeightPx());
	m_framebuffer.bindForRendering();

	populateCommandBuffer(effect);
	executeCommands();
}

void PostProcessor::renderEffectToDisplay(const PEffect& effect)
{
	Framebuffer::bindDefaultForRendering(m_engineProxy.getDisplayWidthPx(), m_engineProxy.getDisplayHeightPx());

	populateCommandBuffer(effect);
	executeCommands();
}

void PostProcessor::populateCommandBuffer(const PEffect& effect)
{
	m_renderCommands.clear();
	effect.genRenderCommands(&m_renderCommands);
}

void PostProcessor::executeCommands()
{
	for(auto& renderCommand : m_renderCommands)
	{
		renderCommand->execute();
	}
}