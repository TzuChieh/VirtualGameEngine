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
};

}