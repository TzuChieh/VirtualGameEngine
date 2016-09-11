#pragma once

#include "Common/type.h"
#include "Physics/PhysicsEngine.h"
#include "Resource/World/Component/TIndexedComponentManager.h"

namespace ve
{

class Engine;

class TestPhysicsEngine : public PhysicsEngine
{
public:
	virtual bool init(Engine* engine) override;
	virtual void update(float32 deltaS) override;
	virtual void decompose() override;

	//virtual std::shared_ptr<ComponentHandle> addTransform(const CTransform& transform) override;

private:
	//TIndexedComponentManager<CTransform> m_transformComponents;
	Engine* m_engine;

};

}