#include "FramebufferRes.h"
#include "Render/Image/Texture2DRes.h"

#include <iostream>

DEFINE_LOG_SENDER(FramebufferRes);

using namespace ve;

void FramebufferRes::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FramebufferRes::bindDefaultForRendering(const uint32 renderWidthPx, const uint32 renderHeightPx)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glViewport(0, 0, static_cast<GLsizei>(renderWidthPx), static_cast<GLsizei>(renderHeightPx));
}

FramebufferRes::FramebufferRes(const uint32 renderWidthPx, const uint32 renderHeightPx) : 
	m_renderWidthPx(renderWidthPx), m_renderHeightPx(renderHeightPx)
{
	glGenFramebuffers(1, &m_framebufferHandle);
}

FramebufferRes::~FramebufferRes()
{
	glDeleteFramebuffers(1, &m_framebufferHandle);

	ENGINE_LOG(FramebufferRes, LogLevel::NOTE_MESSAGE, "ID <" + std::to_string(m_framebufferHandle) + "> deleted");
}

void FramebufferRes::attachRenderTarget(const std::shared_ptr<Texture2DRes>& targetResource, 
                                        const uint32 targetMipLevel, 
                                        const ETargetSlot& targetSlot)
{
	bind();

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
	                       static_cast<GLenum>(targetSlot),
	                       GL_TEXTURE_2D, targetResource->getGlHandle(), static_cast<GLint>(targetMipLevel));

	// we are unlikely going to call any one of the glRead<*> or glCopy<*> APIs
	disableRead();

	ENGINE_LOG_IF(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE,
	              FramebufferRes, LogLevel::FATAL_ERROR,
	              FramebufferRes::getFramebufferResStatusInfo(*this));

	if(isTargetSlotOccupied(targetSlot))
	{
		for(auto& renderTarget : m_texture2dResRenderTargets)
		{
			if(renderTarget.first == targetSlot)
			{
				renderTarget.second = targetResource;
				break;
			}
		}
	}
	else
	{
		m_texture2dResRenderTargets.push_back(std::make_pair(targetSlot, targetResource));
	}

	unbind();
}

void FramebufferRes::detachAllRenderTargets()
{
	bind();

	// TODO: texture level

	for(const auto& renderTarget : m_texture2dResRenderTargets)
	{
		glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
		                       static_cast<GLenum>(renderTarget.first),
		                       GL_TEXTURE_2D, 0, 0);
	}

	m_texture2dResRenderTargets.clear();

	unbind();
}

void FramebufferRes::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_framebufferHandle);
}

void FramebufferRes::unbind() const
{
	FramebufferRes::bindDefault();
}

void FramebufferRes::bindForRendering() const
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebufferHandle);
	glViewport(0, 0, static_cast<GLsizei>(getRenderWidthPx()), static_cast<GLsizei>(getRenderHeightPx()));
}

void FramebufferRes::disableRead() const
{
	bind();
	glReadBuffer(GL_NONE);
	unbind();
}

void FramebufferRes::disableWrite() const
{
	bind();
	glDrawBuffer(GL_NONE);
	unbind();
}

// FIXME: glDrawBuffer"S"!
void FramebufferRes::enableWriteOn(const std::initializer_list<ETargetSlot> targetSlots) const
{
	bind();

	for(const auto& targetSlot : targetSlots)
	{
		if(!isTargetSlotOccupied(targetSlot))
		{
			ENGINE_LOG(FramebufferRes, LogLevel::NOTE_WARNING, "at enableWriteOn(), target slot is empty");
			continue;
		}

		glDrawBuffer(static_cast<GLenum>(targetSlot));
	}

	unbind();
}

void FramebufferRes::setRenderWidthPx(const uint32 widthPx)
{
	m_renderWidthPx = widthPx;
}

void FramebufferRes::setRenderHeightPx(const uint32 heightPx)
{
	m_renderHeightPx = heightPx;
}

void FramebufferRes::setRenderDimensionPx(const uint32 widthPx, const uint32 heightPx)
{
	setRenderWidthPx(widthPx);
	setRenderHeightPx(heightPx);
}

uint32 FramebufferRes::getRenderWidthPx() const
{
	return m_renderWidthPx;
}

uint32 FramebufferRes::getRenderHeightPx() const
{
	return m_renderHeightPx;
}

std::shared_ptr<Texture2DRes> FramebufferRes::getAttachedRenderTarget(const ETargetSlot& targetSlot) const
{
	for(const auto& renderTarget : m_texture2dResRenderTargets)
	{
		if(renderTarget.first == targetSlot)
		{
			return renderTarget.second;
		}
	}

	ENGINE_LOG(FramebufferRes, LogLevel::NOTE_WARNING,
	           "at getAttachedRenderTarget(), target slot is empty, an empty resource is returned");

	return nullptr;
}

bool FramebufferRes::isTargetSlotOccupied(const ETargetSlot& targetSlot) const
{
	for(const auto& renderTarget : m_texture2dResRenderTargets)
	{
		if(renderTarget.first == targetSlot)
		{
			return true;
		}
	}

	return false;
}

std::string FramebufferRes::getFramebufferResStatusInfo(const FramebufferRes& framebufferRes)
{
	std::string messagePrefix = "ID <" + std::to_string(framebufferRes.m_framebufferHandle) + "> status: ";
	std::string message;

	framebufferRes.bind();
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