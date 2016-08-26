#include "Texture.h"

#include <iostream>

using namespace ve;

Texture::Texture(ETextureType textureType) :
	m_textureHandle(nullptr),
	m_textureType(textureType),
	m_textureFilterMode(ETextureFilterMode::LINEAR)
{
	GLuint textureHandle;
	glGenTextures(1, &textureHandle);
	
	m_textureHandle = std::make_shared<GLuint>(textureHandle);
}

Texture::~Texture()
{
	if(m_textureHandle.unique())
	{
		glDeleteTextures(1, m_textureHandle.get());

		std::cout << "texture deleted" << std::endl;
	}
}

TextureId Texture::getId() const
{
	return static_cast<TextureId>(*m_textureHandle);
}

void Texture::bind()
{
	glBindTexture(getGlTextureType(), *m_textureHandle);
}

void Texture::unbind()
{
	glBindTexture(getGlTextureType(), 0);
}

ETextureType Texture::getTextureType() const
{
	return m_textureType;
}

GLenum Texture::getGlTextureType() const
{
	return static_cast<GLenum>(m_textureType);
}

void Texture::setTextureFilterMode(ETextureFilterMode textureFilterMode)
{
	m_textureFilterMode = textureFilterMode;
}

ETextureFilterMode Texture::getTextureFilterMode() const
{
	return m_textureFilterMode;
}

GLfloat Texture::getGlTextureFilterMode() const
{
	return static_cast<GLfloat>(m_textureFilterMode);
}