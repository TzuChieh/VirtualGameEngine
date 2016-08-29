#include "Texture.h"

#include <iostream>

DEFINE_LOG_SENDER(Texture);

using namespace ve;

Texture::Texture() :
	m_textureHandle(nullptr),
	m_textureType(ETextureType::TEXTURE_2D),
	m_textureFilterMode(ETextureFilterMode::LINEAR)
{

}

Texture::~Texture()
{
	if(m_textureHandle.unique())
	{
		glDeleteTextures(1, m_textureHandle.get());

		ENGINE_LOG(Texture, LogLevel::NOTE_MESSAGE, "ID <" + std::to_string(*m_textureHandle) + "> deleted");
	}
}

void Texture::createResource(const ETextureType& textureType)
{
	// TODO: prevent multi-creation

	GLuint textureHandle;
	glGenTextures(1, &textureHandle);
	m_textureHandle = std::make_shared<GLuint>(textureHandle);

	m_textureType = textureType;
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

bool ve::Texture::operator == (const Texture & other) const
{
	if(m_textureHandle == nullptr || other.m_textureHandle == nullptr)
	{
		return false;
	}

	return *m_textureHandle == *(other.m_textureHandle);
}

bool ve::Texture::operator != (const Texture & other) const
{
	return !(*this == other);
}