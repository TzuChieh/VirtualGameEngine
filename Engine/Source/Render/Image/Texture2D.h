#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "Texture2DRes.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(Texture2D);

namespace ve
{

class LdrRectImage;

class Texture2D final
{
public:
	Texture2D();
	Texture2D(const std::shared_ptr<Texture2DRes>& resource);

	bool load(const LdrRectImage& ldrRectImage);
	bool create(const uint32 widthPx, const uint32 heightPx, const ETextureDataFormat dataFormat);

	void use() const;

	bool operator == (const Texture2D& other) const;
	bool operator != (const Texture2D& other) const;

	uint32 getWidthPx() const;
	uint32 getHeightPx() const;
	std::shared_ptr<Texture2DRes> getResource() const;
	bool hasResource() const;

	void setFilterMode(const ETextureFilterMode filterMode);

private:
	std::shared_ptr<Texture2DRes> m_textureResource;
};

}