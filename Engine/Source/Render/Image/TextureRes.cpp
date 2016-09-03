#include "TextureRes.h"

#define OPENGL_DEFAULT_TEXTURE_HANDLE 0

using namespace ve;

GLuint TextureRes::bindedTextureHandle = OPENGL_DEFAULT_TEXTURE_HANDLE;

void TextureRes::clearCachedBindingState()
{
	bindedTextureHandle = OPENGL_DEFAULT_TEXTURE_HANDLE;
}

TextureRes::TextureRes(const ETextureType textureType) : 
	m_textureType(textureType)
{
	glGenTextures(1, &m_textureHandle);

	setTextureFilterMode(ETextureFilterMode::LINEAR);
}

TextureRes::~TextureRes()
{
	glDeleteTextures(1, &m_textureHandle);
}

void TextureRes::bind() const
{
	// FIXME: texture slot! or this is wrong!

	if(bindedTextureHandle != m_textureHandle)
	{
		glBindTexture(static_cast<GLenum>(m_textureType), m_textureHandle);
		bindedTextureHandle = m_textureHandle;
	}
}

void TextureRes::unbind() const
{
	// FIXME: texture slot! or this is wrong!

	if(bindedTextureHandle != OPENGL_DEFAULT_TEXTURE_HANDLE)
	{
		glBindTexture(static_cast<GLenum>(m_textureType), OPENGL_DEFAULT_TEXTURE_HANDLE);
		bindedTextureHandle = OPENGL_DEFAULT_TEXTURE_HANDLE;
	}
}

ETextureType TextureRes::getTextureType() const
{
	return m_textureType;
}

void TextureRes::setTextureFilterMode(const ETextureFilterMode textureFilterMode)
{
	m_textureFilterMode = textureFilterMode;

	bind();

	glTexParameteri(static_cast<GLenum>(m_textureType), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(textureFilterMode));
	glTexParameteri(static_cast<GLenum>(m_textureType), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(textureFilterMode));

	unbind();
}

ETextureFilterMode TextureRes::getTextureFilterMode() const
{
	return m_textureFilterMode;
}

GLuint TextureRes::getGlHandle() const
{
	return m_textureHandle;
}

bool TextureRes::operator == (const TextureRes& other) const
{
	return m_textureHandle == other.m_textureHandle;
}

bool TextureRes::operator != (const TextureRes& other) const
{
	return !(*this == other);
}