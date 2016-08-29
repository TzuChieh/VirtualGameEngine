#include "Brush.h"

using namespace ve;

Brush::~Brush()
{

}

bool Brush::create()
{
	if(!GpuMesh::create())
	{
		return false;
	}

	if(!loadPositionData())
	{
		return false;
	}

	return true;
}