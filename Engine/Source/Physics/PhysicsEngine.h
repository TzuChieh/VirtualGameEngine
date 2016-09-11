#pragma once

#include "Common/type.h"
#include "Resource/World/Component/ComponentHandle.h"

#include <memory>

namespace ve
{

class CTransform;
class Engine;

class PhysicsEngine
{
public:
	virtual bool init(Engine* engine) = 0;
	virtual void update(float32 deltaS) = 0;
	virtual void decompose() = 0;

	//virtual std::shared_ptr<ComponentHandle> addTransform(const CTransform& transform) = 0;
};

}