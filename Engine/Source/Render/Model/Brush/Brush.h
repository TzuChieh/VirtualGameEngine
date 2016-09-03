#pragma once

#include "Render/Model/GpuMesh.h"
#include "Common/logging.h"

#include <memory>

DECLARE_LOG_SENDER_EXTERN(Brush);

namespace ve
{

class Brush : public GpuMesh
{
public:
	Brush();
	virtual ~Brush() override = 0;
};

}