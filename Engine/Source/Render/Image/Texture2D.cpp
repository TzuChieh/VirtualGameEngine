#include "Texture2D.h"
#include "LdrRectImage.h"

DEFINE_LOG_SENDER(Texture2D);

using namespace ve;

Texture2D::Texture2D() : 
	Texture(ETextureType::TEXTURE_2D)
{

}

Texture2D::~Texture2D()
{

}

bool Texture2D::init(const LdrRectImage& ldrRectImage)
{
	ENGINE_LOG(Texture2D, LogLevel::NOTE_MESSAGE, "init with image (" + ldrRectImage.getName() + ")");

	if(!ldrRectImage.isDataValid())
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR, "image (" + ldrRectImage.getName() + ") data is invalid");
		return false;
	}

	bind();

	const GLenum textureType = getGlTextureType();
	const GLenum filterMode  = getGlTextureFilterMode();

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameterf(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, filterMode);

	GLint gpuTextureDataFormat;
	GLenum ldrRectImageDataFormat;
	if(ldrRectImage.getNumComponents() == 3)
	{
		gpuTextureDataFormat = GL_RGB8;
		ldrRectImageDataFormat = GL_RGB;
	}
	else if(ldrRectImage.getNumComponents() == 4)
	{
		gpuTextureDataFormat = GL_RGBA8;
		ldrRectImageDataFormat = GL_RGBA;
	}
	else
	{
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR,
				   "image (" + ldrRectImage.getName() + ") pixel data have " + 
		           std::to_string(ldrRectImage.getNumComponents()) + 
		           " components which is unsupported");
		return false;
	}

	glTexImage2D(textureType, 0, gpuTextureDataFormat,
	             static_cast<GLsizei>(ldrRectImage.getWidthPx()), static_cast<GLsizei>(ldrRectImage.getHeightPx()),
	             0, ldrRectImageDataFormat,
	             GL_UNSIGNED_BYTE, ldrRectImage.getImageData());

	unbind();

	return true;
}

bool Texture2D::init(const uint32 widthPx, const uint32 heightPx,
                     ETextureDataFormat dataFormat, ETextureFilterMode filterMode)
{
	GLint textureDataFormat = GL_RGBA8;
	GLenum imageDataFormat = GL_RGBA;

	switch(dataFormat)
	{
	case ETextureDataFormat::RGB_8_BITS_EACH:
		textureDataFormat = GL_RGB8;
		imageDataFormat = GL_RGB;
		break;

	case ETextureDataFormat::RGBA_8_BITS_EACH:
		textureDataFormat = GL_RGBA8;
		imageDataFormat = GL_RGBA;
		break;

	default:
		ENGINE_LOG(Texture2D, LogLevel::RECOVERABLE_ERROR,
				   "unsupported data format detected, default (RGBA_8_BITS_EACH) is used");
		break;
	}

	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, textureDataFormat,
	             static_cast<GLsizei>(widthPx), static_cast<GLsizei>(heightPx),
	             0, imageDataFormat, GL_UNSIGNED_BYTE, 0);

	setTextureFilterMode(filterMode);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	unbind();

	return true;
}