#pragma once

#include "Common/type.h"

#include "Common/ThirdPartyLib/glew.h"

namespace ve
{

enum class ETextureType : uint32;
enum class ETextureFilterMode : uint32;
enum class ETextureDataFormat : uint32;
enum class EDataFormat : uint32;

class TextureRes
{
public:
	static void clearCachedBindingState();

public:
	TextureRes(const ETextureType textureType);
	virtual ~TextureRes() = 0;

	void bind() const;
	void unbind() const;

	bool operator == (const TextureRes& other) const;
	bool operator != (const TextureRes& other) const;

	ETextureType getTextureType() const;
	ETextureFilterMode getTextureFilterMode() const;
	GLuint getGlHandle() const;

	void setTextureFilterMode(const ETextureFilterMode textureFilterMode);

private:
	GLuint m_textureHandle;

	ETextureType m_textureType;
	ETextureFilterMode m_textureFilterMode;

private:
	static GLuint bindedTextureHandle;
};

enum class ETextureType : uint32
{
	TEXTURE_1D = GL_TEXTURE_1D,
	TEXTURE_2D = GL_TEXTURE_2D,
	TEXTURE_3D = GL_TEXTURE_3D
};

enum class ETextureFilterMode : uint32
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR
};

enum class ETextureDataFormat : uint32
{
	RGB_8_BITS_EACH = GL_RGB8,
	RGBA_8_BITS_EACH = GL_RGBA8,
	DEPTH_24_BITS_STENCIL_8_BITS = GL_DEPTH24_STENCIL8
};

enum class EDataFormat : uint32
{
	RGB_8_BITS_EACH = GL_RGB,
	RGBA_8_BITS_EACH = GL_RGBA,
	DEPTH_24_BITS_STENCIL_8_BITS = GL_DEPTH_STENCIL
};

}