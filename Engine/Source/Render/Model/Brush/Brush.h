#pragma once

#include "Render/Model/GpuMesh.h"

namespace ve
{

class Brush : public GpuMesh
{
public:
	virtual ~Brush() override = 0;

	virtual bool create() final override;

private:
	virtual bool loadPositionData() = 0;
};

}