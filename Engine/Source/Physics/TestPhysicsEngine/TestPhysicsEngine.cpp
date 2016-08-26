#include "TestPhysicsEngine.h"
#include "TransformManagerActionListener.h"

#include <iostream>
#include <memory>

using namespace ve;

bool TestPhysicsEngine::init()
{
	m_transformComponents.addActionListener(std::make_shared<TransformManagerActionListener>());

	return true;
}

void TestPhysicsEngine::update(float32 deltaS)
{
	//std::cout << "physics engine updated" << std::endl;
}

void TestPhysicsEngine::decompose()
{

}

std::shared_ptr<ComponentHandle> TestPhysicsEngine::addTransform(const CTransform& transform)
{
	return m_transformComponents.addComponent(transform);
}