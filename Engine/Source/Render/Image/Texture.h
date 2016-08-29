#pragma once

#include "Common/type.h"
#include "Common/logging.h"

#include "Common/ThirdPartyLib/glew.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(Texture);

namespace ve
{

typedef uint32 TextureId;

enum class ETextureType : uint32;
enum class ETextureFilterMode : uint32;
enum class EGpuTextureDataFormat : uint32;

class Texture
{
public:
	virtual ~Texture() = 0;

	TextureId getId() const;

	inline const std::shared_ptr<GLuint>& getGlTextureHandle() const
	{
		return m_textureHandle;
	}

	bool operator == (const Texture& other) const;
	bool operator != (const Texture& other) const;

protected:
	Texture();

	void createResource(const ETextureType& textureType);

	void bind();
	void unbind();

	ETextureType getTextureType() const;
	GLenum getGlTextureType() const;

	void setTextureFilterMode(ETextureFilterMode textureFilterMode);
	ETextureFilterMode getTextureFilterMode() const;
	GLfloat getGlTextureFilterMode() const;

private:
	std::shared_ptr<GLuint> m_textureHandle;
	ETextureType m_textureType;
	ETextureFilterMode m_textureFilterMode;
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
	LINEAR  = GL_LINEAR
};

enum class ETextureDataFormat : uint32
{
	RGB_8_BITS_EACH  = GL_RGB8,
	RGBA_8_BITS_EACH = GL_RGBA8
};

}