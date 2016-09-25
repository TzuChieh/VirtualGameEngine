#include "World.h"
#include "Resource/World/Entity/EntityData.h"

#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Physics/Component/CTransform.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/World/Component/CTestComponent.h"

#include <iostream>

DEFINE_LOG_SENDER(World);

using namespace ve;

World::World(Engine* engine) :
	m_engine(engine), m_entityDatabase(this)
{

}

World::~World() = default;

bool World::init()
{
	return allocateStorageForCoreComponentTypes();
}

Entity World::createEntity()
{
	return m_entityDatabase.createEntity();
}

void World::removeEntity(const Entity& entity)
{
	m_entityDatabase.removeEntity(entity);
}

void World::flushAttachings()
{
	for(auto& componentAttacher : m_componentAttachers)
	{
		componentAttacher();
	}

	m_componentAttachers.clear();
}

void World::flushDetachings()
{
	for(auto& componentDetacher : m_componentDetachers)
	{
		componentDetacher();
	}

	m_componentDetachers.clear();
}

//EntityId::IndexType World::getEntityIndex(const Entity& entity) const
//{
//	return entity->getEntityId().m_index;
//}

ComponentDatabase* World::getComponentDatabase()
{
	return &m_componentDatabase;
}

EntityDatabase* World::getEntityDatabase()
{
	return &m_entityDatabase;
}

bool World::allocateStorageForCoreComponentTypes()
{
	bool isAllocationSuccess = false;

	isAllocationSuccess |= m_componentDatabase.allocateComponentStorage<CCamera>();
	isAllocationSuccess |= m_componentDatabase.allocateComponentStorage<CStaticModelGroup>();
	isAllocationSuccess |= m_componentDatabase.allocateComponentStorage<CTransform>();
	isAllocationSuccess |= m_componentDatabase.allocateComponentStorage<CGameLogicGroup>();
	isAllocationSuccess |= m_componentDatabase.allocateComponentStorage<CTestComponent>();

	return isAllocationSuccess;
}