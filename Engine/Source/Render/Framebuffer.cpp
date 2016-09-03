#include "Framebuffer.h"
#include "Render/Image/Texture2DRes.h"
#include "FramebufferRes.h"

#include <iostream>

DEFINE_LOG_SENDER(Framebuffer);

using namespace ve;

void Framebuffer::bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx)
{
	FramebufferRes::bindDefaultForRendering(renderWidthPx, renderHeightPx);
}

Framebuffer::Framebuffer() :
	m_framebufferResource(nullptr)
{
	
}

Framebuffer::Framebuffer(const std::shared_ptr<FramebufferRes>& resource) :
	m_framebufferResource(resource)
{
	ENGINE_LOG_IF(!hasResource(), Framebuffer, LogLevel::NOTE_WARNING, "at ctor(), resource is empty");
}

void Framebuffer::attachRenderTarget(const Texture2D& texture2d, const uint32 targetMipLevel, const ETargetSlot& targetSlot)
{
	m_framebufferResource->attachRenderTarget(texture2d.getResource(), targetMipLevel, targetSlot);
}

void Framebuffer::detachAllRenderTargets()
{
	m_framebufferResource->detachAllRenderTargets();
}

void Framebuffer::useForRendering() const
{
	if(!hasResource())
	{
		ENGINE_LOG(Framebuffer, LogLevel::NOTE_WARNING, "at useForRendering(), attempting to use an empty resource");
		return;
	}

	m_framebufferResource->bindForRendering();
}

void Framebuffer::disableRead() const
{
	m_framebufferResource->disableRead();
}

void Framebuffer::disableWrite() const
{
	m_framebufferResource->disableWrite();
}

void Framebuffer::enableWriteOn(const std::initializer_list<ETargetSlot>& targetSlots) const
{
	m_framebufferResource->enableWriteOn(targetSlots);
}

void Framebuffer::setRenderWidthPx(const uint32 widthPx)
{
	m_framebufferResource->setRenderWidthPx(widthPx);
}

void Framebuffer::setRenderHeightPx(const uint32 heightPx)
{
	m_framebufferResource->setRenderHeightPx(heightPx);
}

void Framebuffer::setRenderDimensionPx(const uint32 widthPx, const uint32 heightPx)
{
	m_framebufferResource->setRenderDimensionPx(widthPx, heightPx);
}

uint32 Framebuffer::getRenderWidthPx() const
{
	return m_framebufferResource->getRenderWidthPx();
}

uint32 Framebuffer::getRenderHeightPx() const
{
	return m_framebufferResource->getRenderHeightPx();
}

Texture2D Framebuffer::getAttachedRenderTarget(const ETargetSlot& targetSlot) const
{
	return Texture2D(m_framebufferResource->getAttachedRenderTarget(targetSlot));
}

std::shared_ptr<FramebufferRes> Framebuffer::getResource() const
{
	return m_framebufferResource;
}

bool Framebuffer::hasResource() const
{
	return m_framebufferResource != nullptr;
}