#pragma once

#include "Common/type.h"

#include <array>

namespace ve
{

class RenderCommandInfo final
{
public:
	RenderCommandInfo() : 
		materialId(0), 
		shaderId(0), 
		priority(0)
	{

	}

	uint32 materialId;
	uint32 shaderId;
	uint32 priority;
};

}