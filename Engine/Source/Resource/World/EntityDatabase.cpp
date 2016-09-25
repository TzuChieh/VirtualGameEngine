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

Entity EntityDatabase::createEntity()
{
	// TODO: ref. count

	EntityId entityId = m_entityDataArray.nextStableIndex();
	m_entityDataArray.add(EntityData(entityId, m_parentWorld));

	m_entityComponentIndexMap.initMapping(entityId);

	return Entity(this, entityId);
}

void EntityDatabase::removeEntity(const Entity& entity)
{
	/*if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "cannot remove an EntityData with an invalid ID");
		return;
	}*/

	// TODO: ref. count

	// TODO: reduce use count & remove all associated components

	if(!m_entityDataArray.remove(entity.getEntityId()))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING,
		           "cannot remove an Entity with an invalid ID");
	}
}

Entity EntityDatabase::getEntity(const EntityId entityId)
{
	// TODO: ref. count

	if(!warnedIsEntityIdValid(entityId))
	{
		return Entity(nullptr, 0);
	}

	return Entity(this, entityId);
}

EntityData* EntityDatabase::getEntityData(const EntityId entityId)
{
	if(!warnedIsEntityIdValid(entityId))
	{
		return nullptr;
	}

	return &(m_entityDataArray[entityId]);
}

bool EntityDatabase::isEntityIdValid(const EntityId entityId) const
{
	return m_entityDataArray.isStableIndexValid(entityId);
}

bool EntityDatabase::warnedIsEntityIdValid(const EntityId entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING, "invalid entity ID detected");
		return false;
	}

	return true;
}

}// end namespace ve