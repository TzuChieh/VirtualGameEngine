#pragma once

#include "Common/type.h"
#include "Common/ThirdPartyLib/glew.h"
#include "Render/Image/Texture2D.h"

#include <vector>
#include <memory>

namespace xe
{

enum class EAttachmentType : uint32;

class Framebuffer
{
public:
	Framebuffer(const uint32 widthPx, const uint32 heightPx);
	~Framebuffer();

	void bind() const;
	void unbind() const;

	// these are per-framebuffer states; no need to specify them everytime you bind
	void disableRead() const;
	void disableWrite() const;

	bool addRenderTarget(const Texture2D& texture2d, const EAttachmentType attachmentType);

private:
	std::shared_ptr<GLuint> m_framebufferHandle;

	uint32 m_widthPx;
	uint32 m_heightPx;

	std::vector<Texture2D> m_texture2dRenderTargets;
};

enum class EAttachmentType : uint32
{
	COLOR_0 = GL_COLOR_ATTACHMENT0,
	COLOR_1 = GL_COLOR_ATTACHMENT1,
	COLOR_2 = GL_COLOR_ATTACHMENT2,
	COLOR_3 = GL_COLOR_ATTACHMENT3,
	COLOR_4 = GL_COLOR_ATTACHMENT4,
	COLOR_5 = GL_COLOR_ATTACHMENT5,

	DEPTH_STENCIL = GL_DEPTH_STENCIL_ATTACHMENT
};

}