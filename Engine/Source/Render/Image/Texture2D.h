#pragma once

#include "Common/type.h"
#include "Texture.h"
#include "Common/logging.h"

DECLARE_LOG_SENDER_EXTERN(Texture2D);

namespace ve
{

class LdrRectImage;

class Texture2D : public Texture
{
public:
	Texture2D();
	virtual ~Texture2D() override;

	bool create(const LdrRectImage& ldrRectImage);
	bool create(const uint32 widthPx, const uint32 heightPx,
	            ETextureDataFormat dataFormat, ETextureFilterMode filterMode);

	inline uint32 getWidthPx() const
	{
		return m_widthPx;
	}

	inline uint32 getHeightPx() const
	{
		return m_heightPx;
	}

private:
	uint32 m_widthPx;
	uint32 m_heightPx;
};

}