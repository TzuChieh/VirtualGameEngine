#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"

namespace xe
{

class Framebuffer
{
public:
	Framebuffer(const uint32 widthPx, const uint32 heightPx);
	~Framebuffer();

private:
	uint32 m_widthPx;
	uint32 m_heightPx;

	GLuint m_framebufferHandle;
};

}