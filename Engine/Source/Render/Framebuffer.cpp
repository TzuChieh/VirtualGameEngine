#include "Framebuffer.h"

#include <iostream>

using namespace xe;

Framebuffer::Framebuffer(const uint32 widthPx, const uint32 heightPx) :
	m_framebufferHandle(nullptr),
	m_widthPx(widthPx),
	m_heightPx(heightPx)
{
	GLuint framebufferHandle;
	glGenFramebuffers(1, &framebufferHandle);

	m_framebufferHandle = std::make_shared<GLuint>(framebufferHandle);
}

Framebuffer::~Framebuffer()
{
	if(m_framebufferHandle.unique())
	{
		glDeleteFramebuffers(1, m_framebufferHandle.get());

		std::cout << "framebuffer deleted" << std::endl;
	}
}

bool Framebuffer::addRenderTarget(const Texture2D& texture2d, const EAttachmentType attachmentType)
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_framebufferHandle);

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
	                       static_cast<GLenum>(attachmentType),
	                       GL_TEXTURE_2D, *(texture2d.getTextureHandle()), 0);

	// TODO

	/*if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Debug.printErr("Framebuffer Error: framebuffer failed while adding render target");
		Debug.printErr("@attachment: " + attachment);

		Exception e = new Exception();
		e.printStackTrace();

		System.exit(1);
	}

	m_textures.add(texture);*/

	return true;
}

void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_framebufferHandle);
}

void Framebuffer::unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::disableRead() const
{
	bind();
	glReadBuffer(GL_NONE);
	unbind();
}

void Framebuffer::disableWrite() const
{
	bind();
	glDrawBuffer(GL_NONE);
	unbind();
}