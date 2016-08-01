#pragma once

#include "Common/type.h"
#include "Physics/PhysicsEngine.h"

namespace xe
{

class TestPhysicsEngine : public PhysicsEngine
{
public:
	virtual bool init() override;
	virtual void update(float32 deltaS) override;
	virtual void decompose() override;
};

}