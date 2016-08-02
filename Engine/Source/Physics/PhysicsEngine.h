#pragma once

#include "Common/type.h"
#include "Resource/Component/ComponentHandle.h"

#include <memory>

namespace xe
{

class CTransform;

class PhysicsEngine
{
public:
	virtual bool init() = 0;
	virtual void update(float32 deltaS) = 0;
	virtual void decompose() = 0;

	virtual std::shared_ptr<ComponentHandle> addTransform(const CTransform& transform) = 0;
};

}