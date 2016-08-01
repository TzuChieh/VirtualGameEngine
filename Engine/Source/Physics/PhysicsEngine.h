#pragma once

#include "Common/type.h"

namespace xe
{

class PhysicsEngine
{
public:
	virtual bool init() = 0;
	virtual void update(float32 deltaS) = 0;
	virtual void decompose() = 0;
};

}