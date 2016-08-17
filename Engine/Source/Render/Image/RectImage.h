#pragma once

#include "Common/type.h"
#include "Image.h"

namespace xe
{

class RectImage : Image
{
public:
	virtual ~RectImage() = 0;

	virtual bool load(const std::string& fullFilename) = 0;
	virtual std::string getName() const = 0;

	inline uint32 getWidthPx()       const { return m_widthPx;       }
	inline uint32 getHeightPx()      const { return m_heightPx;      }
	inline uint32 getNumComponents() const { return m_numComponents; }

protected:
	inline void setDimensionPx(const uint32 widthPx, const uint32 heightPx, const uint32 numComponents)
	{
		m_widthPx       = widthPx;
		m_heightPx      = heightPx;
		m_numComponents = numComponents;
	}

private:
	uint32 m_widthPx;
	uint32 m_heightPx;
	uint32 m_numComponents;
};

}