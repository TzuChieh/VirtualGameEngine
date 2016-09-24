#include "EntityDatabase.h"
#include "World.h"
#include "Resource/World/Entity/EntityData.h"

DEFINE_LOG_SENDER(EntityDatabase);

namespace ve
{

EntityDatabase::EntityDatabase(World* const world) :
	m_parentWorld(world)
{
	ENGINE_LOG_IF(world == nullptr, EntityDatabase, LogLevel::NOTE_WARNING, "world is null");
}

EntityDatabase::~EntityDatabase() = default;

std::shared_ptr<EntityData> EntityDatabase::createEntityData()
{
	EntityId entityId;
	std::shared_ptr<EntityData> entityData;

	if(m_availableEntityIds.empty())
	{
		entityId.m_index = m_validEntitySerials.size();
		entityId.m_serial = EntityId::invalidSerial + 1;

		m_validEntitySerials.push_back(entityId.m_serial);
		m_entityDataVector.push_back(entityData);
	}
	else
	{
		entityId = m_availableEntityIds.back();
		m_availableEntityIds.pop_back();
	}

	m_entityComponentIndexMap.initMapping(entityId.m_index);

	entityData = std::make_shared<EntityData>(entityId, m_parentWorld);
	m_entityDataVector[entityId.m_index] = entityData;


	m_test.push_back(*entityData);

	return entityData;
}

void EntityDatabase::removeEntityData(const EntityId& entityId)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "cannot remove an EntityData with an invalid ID");
		return;
	}

	// generate a new EntityId and store it for later use
	EntityId newEntityId(entityId);
	newEntityId.m_serial++;
	m_availableEntityIds.push_back(newEntityId);
	m_validEntitySerials[newEntityId.m_index] = newEntityId.m_serial;

	m_entityDataVector[entityId.m_index] = nullptr;
}

std::shared_ptr<EntityData> EntityDatabase::getEntityData(const EntityId& entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "cannot get an EntityFunctionality with an invalid ID");
		return nullptr;
	}

	return m_entityDataVector[entityId.m_index];
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