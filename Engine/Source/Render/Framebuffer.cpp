#include "Framebuffer.h"

#include <iostream>

DEFINE_LOG_SENDER(Framebuffer);

using namespace ve;

void Framebuffer::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, static_cast<GLsizei>(renderWidthPx), static_cast<GLsizei>(renderHeightPx));
}

Framebuffer::Framebuffer() :
	m_framebufferHandle(nullptr)
{
	
}

Framebuffer::~Framebuffer()
{
	if(m_framebufferHandle.unique())
	{
		glDeleteFramebuffers(1, m_framebufferHandle.get());

		ENGINE_LOG(Framebuffer, LogLevel::NOTE_MESSAGE, "ID <" + std::to_string(*m_framebufferHandle) + "> deleted");
	}
}

void Framebuffer::create(const uint32 widthPx, const uint32 heightPx)
{
	setRenderWidthPx(widthPx);
	setRenderHeightPx(heightPx);

	// TODO: prevent multi-creation

	GLuint framebufferHandle;
	glGenFramebuffers(1, &framebufferHandle);

	m_framebufferHandle = std::make_shared<GLuint>(framebufferHandle);
}

void Framebuffer::create()
{
	create(0, 0);
}

void Framebuffer::attachRenderTarget(const Texture2D& texture2d, const ETargetSlot& targetSlot)
{
	bind();

	// TODO: texture level

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
	                       static_cast<GLenum>(targetSlot),
	                       GL_TEXTURE_2D, *(texture2d.getGlTextureHandle()), 0);

	// we are unlikely going to call any one of the glRead<*> or glCopy<*> APIs
	disableRead();

	ENGINE_LOG_IF(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, 
		          Framebuffer, LogLevel::FATAL_ERROR,
		          Framebuffer::getFramebufferStatusInfo(*this));

	if(isTargetSlotOccupied(targetSlot))
	{
		for(auto& renderTarget : m_texture2dRenderTargets)
		{
			if(renderTarget.first == targetSlot)
			{
				renderTarget.second = texture2d;
				break;
			}
		}
	}
	else
	{
		m_texture2dRenderTargets.push_back(std::make_pair(targetSlot, texture2d));

		std::cout << "attached" << std::endl;
		std::cout << isTargetSlotOccupied(targetSlot) << std::endl;
		std::cout << static_cast<int32>(targetSlot) << std::endl;
	}
}

void Framebuffer::detachAllRenderTargets()
{
	bind();

	// TODO: texture level

	for(const auto& renderTarget : m_texture2dRenderTargets)
	{
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
		                       static_cast<GLenum>(renderTarget.first),
		                       GL_TEXTURE_2D, 0, 0);
	}

	m_texture2dRenderTargets.clear();
}

void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_framebufferHandle);
}

void Framebuffer::unbind() const
{
	Framebuffer::bindDefault();
}

void Framebuffer::bindForRendering() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, *m_framebufferHandle);
	glViewport(0, 0, static_cast<GLsizei>(getRenderWidthPx()), static_cast<GLsizei>(getRenderHeightPx()));
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

// FIXME: glDrawBuffer"S"!
void Framebuffer::enableWriteOn(const std::initializer_list<ETargetSlot> targetSlots) const
{
	bind();

	for(const auto& targetSlot : targetSlots)
	{
		std::cout << static_cast<int32>(targetSlot) << std::endl;

		if(!isTargetSlotOccupied(targetSlot))
		{
			ENGINE_LOG(Framebuffer, LogLevel::NOTE_WARNING, "at enableWriteOn(), target slot is empty");
			continue;
		}

		glDrawBuffer(static_cast<GLenum>(targetSlot));
	}

	unbind();
}

void Framebuffer::setRenderWidthPx(const uint32 widthPx)
{
	m_renderWidthPx = widthPx;
}

void Framebuffer::setRenderHeightPx(const uint32 heightPx)
{
	m_renderHeightPx = heightPx;
}

void Framebuffer::setRenderDimensionPx(const uint32 widthPx, const uint32 heightPx)
{
	setRenderWidthPx(widthPx);
	setRenderHeightPx(heightPx);
}

uint32 Framebuffer::getRenderWidthPx() const
{
	return m_renderWidthPx;
}

uint32 Framebuffer::getRenderHeightPx() const
{
	return m_renderHeightPx;
}

Texture2D Framebuffer::getAttachedRenderTarget(const ETargetSlot& targetSlot) const
{
	for(const auto& renderTarget : m_texture2dRenderTargets)
	{
		if(renderTarget.first == targetSlot)
		{
			return renderTarget.second;
		}
	}

	ENGINE_LOG(Framebuffer, LogLevel::NOTE_WARNING,
	           "at getAttachedRenderTarget(), target slot is empty, an empty Texture2D is returned");

	return Texture2D();
}

bool Framebuffer::isTargetSlotOccupied(const ETargetSlot& targetSlot) const
{
	for(const auto& renderTarget : m_texture2dRenderTargets)
	{
		if(renderTarget.first == targetSlot)
		{
			return true;
		}
	}

	return false;
}

std::string Framebuffer::getFramebufferStatusInfo(const Framebuffer& framebuffer)
{
	std::string messagePrefix = "ID <" + std::to_string(*framebuffer.m_framebufferHandle) + "> status: ";
	std::string message;

	framebuffer.bind();
	GLenum statusCode = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch(statusCode)
	{
	case GL_FRAMEBUFFER_COMPLETE:
		message = "Complete, no error.";
		break;

	case GL_FRAMEBUFFER_UNDEFINED:
		message = "The specified framebuffer is the default read or draw framebuffer, but "
		          "the default framebuffer does not exist.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
		message = "One or more of the framebuffer attachment points are framebuffer incomplete.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
		message = "The framebuffer does not have at least one image attached to it.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
		message = "The value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE for any color attachment point(s) "
		          "named by GL_DRAW_BUFFERi.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
		message = "GL_READ_BUFFER is not GL_NONE and the value of GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE is GL_NONE "
		          "for the color attachment point named by GL_READ_BUFFER.";
		break;

	case GL_FRAMEBUFFER_UNSUPPORTED:
		message = "The combination of internal formats of the attached images violates an implementation-dependent "
		          "set of restrictions.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
		message = "Two possible errors: 1. The value of GL_RENDERBUFFER_SAMPLES is not the same for all attached "
		          "renderbuffers; if the value of GL_TEXTURE_SAMPLES is the not same for all attached textures; "
		          "or, if the attached images are a mix of renderbuffers and textures, the value of "
		          "GL_RENDERBUFFER_SAMPLES does not match the value of GL_TEXTURE_SAMPLES. 2. The value of "
		          "GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is not the same for all attached textures; or, if the attached "
		          "images are a mix of renderbuffers and textures, the value of GL_TEXTURE_FIXED_SAMPLE_LOCATIONS is "
		          "not GL_TRUE for all attached textures.";
		break;

	case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
		message = "One or more framebuffer attachment are layered, and one or more populated attachment are not "
		          "layered, or if all populated color attachments are not from textures of the same target.";
		break;

	default:
		message = "Unknown error.";
		break;
	}

	return messagePrefix + message;
}