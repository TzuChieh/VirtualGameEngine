#include "Brush.h"
#include "Render/Model/GpuMeshRes.h"

DEFINE_LOG_SENDER(Brush);

using namespace ve;

Brush::Brush() : 
	GpuMesh(std::make_shared<GpuMeshRes>())
{
	
}

Brush::~Brush() = default;