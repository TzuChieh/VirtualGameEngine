#include "TextureRes.h"

using namespace ve;

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
	glBindTexture(static_cast<GLenum>(m_textureType), m_textureHandle);
}

void TextureRes::unbind() const
{
	glBindTexture(static_cast<GLenum>(m_textureType), 0);
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