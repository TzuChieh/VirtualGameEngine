#include "World.h"
#include "Resource/World/Entity/EntityFunctionality.h"

#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Physics/Component/CTransform.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Resource/World/Component/CTestComponent.h"

#include <iostream>

DEFINE_LOG_SENDER(World);

using namespace ve;

World::World(Engine* engine) :
	m_engine(engine)
{

}

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
	EntityId entityId;
	std::shared_ptr<EntityFunctionality> entityFunctionality;

	if(m_availableEntityIds.empty())
	{
		entityId.m_index = m_validEntitySerials.size();
		entityId.m_serial = EntityId::invalidSerial + 1;

		m_validEntitySerials.push_back(entityId.m_serial);
		m_entityFunctionalities.push_back(entityFunctionality);
	}
	else
	{
		entityId = m_availableEntityIds.back();
		m_availableEntityIds.pop_back();
	}

	m_entityComponentDatabase.initComponentsIndexMapping(entityId.m_index);

	entityFunctionality = std::make_shared<EntityFunctionality>(entityId, this);
	m_entityFunctionalities[entityId.m_index] = entityFunctionality;
	return entityFunctionality;
}

void World::removeEntityFunctionality(const EntityId& entityId)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING,
		           "cannot remove an EntityFunctionality with an invalid ID");
		return;
	}

	// generate a new EntityId and store it for later use
	EntityId newEntityId(entityId);
	newEntityId.m_serial++;
	m_availableEntityIds.push_back(newEntityId);
	m_validEntitySerials[newEntityId.m_index] = newEntityId.m_serial;

	m_entityFunctionalities[entityId.m_index] = nullptr;
}

std::shared_ptr<EntityFunctionality> World::getEntityFunctionality(const EntityId& entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING,
		           "cannot get an EntityFunctionality with an invalid ID");
		return nullptr;
	}

	return m_entityFunctionalities[entityId.m_index];
}

bool World::isEntityIdValid(const EntityId& entityId) const
{
	if(entityId.m_index < m_validEntitySerials.size())
	{
		if(m_validEntitySerials[entityId.m_index] != entityId.m_serial)
		{
			ENGINE_LOG(World, LogLevel::NOTE_WARNING,
			           "invalid entity detected - entity serial is invalid");
			return false;
		}
	}
	else
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING,
		           "invalid entity detected - entity index is invalid");
		return false;
	}

	return true;
}

EntityId::IndexType World::getEntityIndex(const Entity& entity) const
{
	return entity->getEntityId().m_index;
}

bool World::allocateStorageForCoreComponentTypes()
{
	bool isAllocationSuccess = false;

	isAllocationSuccess |= m_entityComponentDatabase.allocateComponentStorage<CCamera>();
	isAllocationSuccess |= m_entityComponentDatabase.allocateComponentStorage<CStaticModelGroup>();
	isAllocationSuccess |= m_entityComponentDatabase.allocateComponentStorage<CTransform>();
	isAllocationSuccess |= m_entityComponentDatabase.allocateComponentStorage<CGameLogicGroup>();
	isAllocationSuccess |= m_entityComponentDatabase.allocateComponentStorage<CTestComponent>();

	return isAllocationSuccess;
}