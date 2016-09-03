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

	bool load2dTexureCoordinateData(const uint32 texCoordGpuAccessIndex);

private:
	uint32 m_positionGpuAccessIndex;
	uint32 m_texCoordGpuAccessIndex;

	bool loadPositionData();
};

}