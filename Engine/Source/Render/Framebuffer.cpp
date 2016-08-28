#include "Framebuffer.h"

#include <iostream>

DEFINE_LOG_SENDER(Framebuffer);

using namespace ve;

void Framebuffer::bindDefault()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
	m_widthPx = widthPx;
	m_heightPx = heightPx;

	// TODO: prevent multi-creation

	GLuint framebufferHandle;
	glGenFramebuffers(1, &framebufferHandle);

	m_framebufferHandle = std::make_shared<GLuint>(framebufferHandle);
}

void Framebuffer::attachRenderTarget(const Texture2D& texture2d, const ETargetTag& targetTag)
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_framebufferHandle);

	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER,
	                       static_cast<GLenum>(targetTag),
	                       GL_TEXTURE_2D, *(texture2d.getGlTextureHandle()), 0);

	// we are not going to call any one of the glRead<*> or glCopy<*> APIs
	disableRead();

	ENGINE_LOG_IF(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE, 
		          Framebuffer, LogLevel::FATAL_ERROR,
		          Framebuffer::getFramebufferStatusInfo(*this));

	m_texture2dRenderTargets.push_back(std::make_pair(targetTag, texture2d));
}

void Framebuffer::bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, *m_framebufferHandle);
}

void Framebuffer::unbind() const
{
	Framebuffer::bindDefault();
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

void Framebuffer::enableWriteOn(const std::initializer_list<ETargetTag> targetTags) const
{
	bind();

	for(const auto& targetTag : targetTags)
	{
		if(!isTargetAttached(targetTag));
		{
			ENGINE_LOG(Framebuffer, LogLevel::NOTE_WARNING, "at enableWriteOn(), speficied target does not exist");
			continue;
		}

		glDrawBuffer(static_cast<GLenum>(targetTag));
	}

	unbind();
}

bool Framebuffer::isTargetAttached(const ETargetTag& targetTag) const
{
	for(const auto& renderTarget : m_texture2dRenderTargets)
	{
		if(renderTarget.first == targetTag)
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