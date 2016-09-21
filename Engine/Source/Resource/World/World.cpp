#include "World.h"
#include "Resource/World/Entity/EntityFunctionality.h"
#include "Resource/World/EntityDatabase.h"

#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Physics/Component/CTransform.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/World/Component/CTestComponent.h"

#include <iostream>

DEFINE_LOG_SENDER(World);

using namespace ve;

World::World(Engine* engine) :
	m_engine(engine), m_entityDatabase(nullptr)
{
	m_entityDatabase = std::make_unique<EntityDatabase>(this);
}

World::~World() = default;

bool World::init()
{
	return allocateStorageForCoreComponentTypes();
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

std::shared_ptr<EntityFunctionality> World::createEntityFunctionality()
{
	return m_entityDatabase->createEntityFunctionality();
}

void World::removeEntityFunctionality(const EntityId& entityId)
{
	m_entityDatabase->removeEntityFunctionality(entityId);
}

std::shared_ptr<EntityFunctionality> World::getEntityFunctionality(const EntityId& entityId) const
{
	return m_entityDatabase->getEntityFunctionality(entityId);
}

bool World::isEntityIdValid(const EntityId& entityId) const
{
	return m_entityDatabase->isEntityIdValid(entityId);
}

EntityId::IndexType World::getEntityIndex(const Entity& entity) const
{
	return entity->getEntityId().m_index;
}

ComponentDatabase* World::getComponentDatabase()
{
	return &m_componentDatabase;
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