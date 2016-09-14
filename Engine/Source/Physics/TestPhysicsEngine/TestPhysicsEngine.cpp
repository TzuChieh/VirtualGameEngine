#include "TestPhysicsEngine.h"
#include "Core/Engine.h"
#include "Resource/World/World.h"
#include "Resource/World/EntityComponentDatabase.h"
#include "Physics/Component/CTransform.h"

#include <iostream>
#include <memory>

using namespace ve;

bool TestPhysicsEngine::init(Engine* engine)
{
	m_engine = engine;

	engine->getWorld()->addComponentListener(&m_transformComponentProcessor);

	return true;
}

void TestPhysicsEngine::update(float32 deltaS)
{
	//std::cout << "physics engine updated" << std::endl;

	World* world = m_engine->getWorld();
	EntityComponentDatabase* database = world->getEntityComponentDatabase();
	auto* transformStorage = database->getComponentStorage<CTransform>();

	for(auto& transform : *transformStorage)
	{
		std::cout << transform.getPosition().toStringFormal() << std::endl;
	}
}

void TestPhysicsEngine::decompose()
{

}

//std::shared_ptr<ComponentHandle> TestPhysicsEngine::addTransform(const CTransform& transform)
//{
//	return m_transformComponents.addComponent(transform);
//}