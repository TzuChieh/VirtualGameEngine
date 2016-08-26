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

	bool init(const LdrRectImage& ldrRectImage);
	bool init(const uint32 widthPx, const uint32 heightPx,
	          ETextureDataFormat dataFormat, ETextureFilterMode filterMode);
};

}