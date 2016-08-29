#pragma once

#include "Common/logging.h"
#include "Brush.h"

DECLARE_LOG_SENDER_EXTERN(Quad2dBrush);

namespace ve
{

class Quad2dBrush final : public Brush
{
public:
	Quad2dBrush(const uint32 positionGpuAccessIndex);
	virtual ~Quad2dBrush() override;

	inline uint32 getPositionGpuAccessIndex() const
	{
		return m_positionGpuAccessIndex;
	}

private:
	virtual bool loadBrushData() override;

	uint32 m_positionGpuAccessIndex;
};

}