#include "Texture2DRes.h"

DEFINE_LOG_SENDER(Texture2DRes);

using namespace ve;

Texture2DRes::Texture2DRes() : 
	TextureRes(ETextureType::TEXTURE_2D)
{

}

Texture2DRes::~Texture2DRes()
{

}

bool Texture2DRes::loadData(const uint32 widthPx, const uint32 heightPx, const EDataFormat dataFormat, const void* data,
                            const uint32 targetMipLevel, const ETextureDataFormat gpuFormat)
{
	setDimension(widthPx, heightPx);
	
	if(!isLdr(dataFormat))
	{
		ENGINE_LOG(Texture2DRes, LogLevel::NOTE_WARNING, "at loadData(), EDataFormat is not LDR, not supported");
		return false;
	}

	const GLenum textureType = static_cast<GLenum>(getTextureType());
	const GLenum sourceDatumType = GL_UNSIGNED_BYTE;

	bind();

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType,
	             static_cast<GLint>(targetMipLevel), 
	             static_cast<GLint>(gpuFormat),
	             static_cast<GLsizei>(widthPx), static_cast<GLsizei>(heightPx), 0, 
	             static_cast<GLenum>(dataFormat), sourceDatumType, data);

	unbind();

	return true;
}

bool Texture2DRes::asRenderTarget(const uint32 widthPx, const uint32 heightPx, const ETextureDataFormat gpuFormat)
{
	setDimension(widthPx, heightPx);

	GLint targetDataFormat = GL_RGBA8;
	GLenum imageDataFormat = GL_RGBA;
	GLenum sourceDatumType = GL_UNSIGNED_BYTE;

	switch(gpuFormat)
	{
	case ETextureDataFormat::RGB_8_BITS_EACH:
		targetDataFormat = GL_RGB8;
		imageDataFormat = GL_RGB;
		sourceDatumType = GL_UNSIGNED_BYTE;
		break;

	case ETextureDataFormat::RGBA_8_BITS_EACH:
		targetDataFormat = GL_RGBA8;
		imageDataFormat = GL_RGBA;
		sourceDatumType = GL_UNSIGNED_BYTE;
		break;

	case ETextureDataFormat::DEPTH_24_BITS_STENCIL_8_BITS:
		targetDataFormat = GL_DEPTH24_STENCIL8;
		imageDataFormat = GL_DEPTH_STENCIL;
		sourceDatumType = GL_UNSIGNED_INT_24_8;
		break;

	default:
		ENGINE_LOG(Texture2DRes, LogLevel::RECOVERABLE_ERROR,
		           "unsupported render target data format detected, default (RGBA_8_BITS_EACH) is used");
		break;
	}

	bind();

	glTexImage2D(static_cast<GLint>(getTextureType()),
	             0,
	             static_cast<GLint>(gpuFormat),
	             static_cast<GLsizei>(widthPx), static_cast<GLsizei>(heightPx), 0,
	             imageDataFormat, sourceDatumType, nullptr);

	glTexParameteri(static_cast<GLint>(getTextureType()), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(static_cast<GLint>(getTextureType()), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unbind();

	return true;
}

void Texture2DRes::setDimension(const uint32 widthPx, const uint32 heightPx)
{
	m_widthPx = widthPx;
	m_heightPx = heightPx;
}

bool Texture2DRes::isLdr(const EDataFormat dataFormat)
{
	return dataFormat == EDataFormat::RGBA_8_BITS_EACH || dataFormat == EDataFormat::RGB_8_BITS_EACH;
}