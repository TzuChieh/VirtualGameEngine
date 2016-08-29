#include "PostProcessor.h"
#include "PEffect.h"
#include "Render/RenderCommand/RenderCommand.h"
#include "Render/Framebuffer.h"

using namespace ve;

bool PostProcessor::init()
{
	return true;
}

void PostProcessor::decompose()
{
	
}

void PostProcessor::renderEffectToTexture(const PEffect& effect, const Texture2D& destination)
{
	// TODO: attach & detach from framebuffer

	populateCommandBuffer(effect);
	executeCommands();
}

void PostProcessor::renderEffectToDisplay(const PEffect& effect)
{
	Framebuffer::bindDefault();

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