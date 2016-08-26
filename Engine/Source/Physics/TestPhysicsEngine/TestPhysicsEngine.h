#pragma once

#include "Common/type.h"
#include "Physics/PhysicsEngine.h"
#include "Resource/Component/TIndexedComponentManager.h"
#include "Physics/Component/CTransform.h"

namespace ve
{

class TestPhysicsEngine : public PhysicsEngine
{
public:
	virtual bool init() override;
	virtual void update(float32 deltaS) override;
	virtual void decompose() override;

	virtual std::shared_ptr<ComponentHandle> addTransform(const CTransform& transform) override;

private:
	TIndexedComponentManager<CTransform> m_transformComponents;
};

}