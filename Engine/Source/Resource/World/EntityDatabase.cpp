#include "EntityDatabase.h"
#include "World.h"
#include "Resource/World/Entity/EntityFunctionality.h"

DEFINE_LOG_SENDER(EntityDatabase);

namespace ve
{

EntityDatabase::EntityDatabase(World* const world) :
	m_parentWorld(world)
{
	ENGINE_LOG_IF(world == nullptr, EntityDatabase, LogLevel::NOTE_WARNING, "world is null");
}

EntityDatabase::~EntityDatabase() = default;

std::shared_ptr<EntityFunctionality> EntityDatabase::createEntityFunctionality()
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

	m_entityComponentIndexMap.initMapping(entityId.m_index);

	entityFunctionality = std::make_shared<EntityFunctionality>(entityId, m_parentWorld);
	m_entityFunctionalities[entityId.m_index] = entityFunctionality;


	m_test.push_back(*entityFunctionality);

	return entityFunctionality;
}

void EntityDatabase::removeEntityFunctionality(const EntityId& entityId)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
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

std::shared_ptr<EntityFunctionality> EntityDatabase::getEntityFunctionality(const EntityId& entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "cannot get an EntityFunctionality with an invalid ID");
		return nullptr;
	}

	return m_entityFunctionalities[entityId.m_index];
}

bool EntityDatabase::isEntityIdValid(const EntityId& entityId) const
{
	if(entityId.m_index < m_validEntitySerials.size())
	{
		if(m_validEntitySerials[entityId.m_index] != entityId.m_serial)
		{
			ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
			           "invalid entity detected - entity serial is invalid");
			return false;
		}
	}
	else
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "invalid entity detected - entity index is invalid");
		return false;
	}

	return true;
}

}// end namespace ve