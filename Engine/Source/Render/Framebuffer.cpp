#include "Framebuffer.h"

using namespace xe;

Framebuffer::Framebuffer(const uint32 widthPx, const uint32 heightPx) :
	m_widthPx(widthPx),
	m_heightPx(heightPx)
{
	glGenFramebuffers(1, &m_framebufferHandle);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &m_framebufferHandle);
}