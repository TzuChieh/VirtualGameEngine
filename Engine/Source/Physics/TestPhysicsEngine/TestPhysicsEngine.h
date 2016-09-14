#pragma once

#include "Common/type.h"
#include "Physics/PhysicsEngine.h"
#include "TransformComponentProcessor.h"

namespace ve
{

class Engine;

class TestPhysicsEngine : public PhysicsEngine
{
public:
	virtual bool init(Engine* engine) override;
	virtual void update(float32 deltaS) override;
	virtual void decompose() override;

private:
	Engine* m_engine;
	TransformComponentProcessor m_transformComponentProcessor;
};

}