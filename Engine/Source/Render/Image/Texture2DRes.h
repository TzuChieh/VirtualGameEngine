#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "TextureRes.h"

DECLARE_LOG_SENDER_EXTERN(Texture2DRes);

namespace ve
{

class Texture2DRes final : public TextureRes
{
public:
	Texture2DRes();
	virtual ~Texture2DRes() override;

	bool loadData(const uint32 widthPx, const uint32 heightPx, const EDataFormat dataFormat, const void* data, 
	              const uint32 targetMipLevel, const ETextureDataFormat gpuFormat);

	bool asRenderTarget(const uint32 widthPx, const uint32 heightPx, const ETextureDataFormat gpuFormat);

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

	void setDimension(const uint32 widthPx, const uint32 heightPx);

	static bool isLdr(const EDataFormat dataFormat);
};

}