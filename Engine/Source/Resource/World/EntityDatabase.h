#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/Entity/EntityComponentIndexMap.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Entity/Entity.h"
#include "Utility/TStableIndexDenseArray.h"

DECLARE_LOG_SENDER_EXTERN(EntityDatabase);

namespace ve
{

class EntityData;
class World;

class EntityDatabase final
{
public:
	explicit EntityDatabase(World* const world);
	~EntityDatabase();

	// Create, remove and get an entity.
	Entity createEntity();
	void removeEntity(const Entity& entity);
	Entity getEntity(const EntityId entityId);
	EntityData* getEntityData(const EntityId entityId);

	// Check if an entity ID is valid for current database.
	bool isEntityIdValid(const EntityId entityId) const;
	bool warnedIsEntityIdValid(const EntityId entityId) const;

	// Map entity index to component indices.
	//
		template<typename ComponentType>
		void mapComponentIndex(const EntityId entityId, const ComponentIndexType index);

		template<typename ComponentType>
		void unmapComponentIndex(const EntityId entityId);

		template<typename ComponentType>
		ComponentIndexType getMappedComponentIndex(const EntityId entityId) const;

	// forbid copying
	EntityDatabase(const EntityDatabase& other) = delete;
	EntityDatabase& operator = (const EntityDatabase& rhs) = delete;

private:
	World* m_parentWorld;

	TStableIndexDenseArray<EntityData> m_entityDataArray;
	EntityComponentIndexMap m_entityComponentIndexMap;
};

// Templated method implementations:

// Implementations:

template<typename ComponentType>
void EntityDatabase::mapComponentIndex(const EntityId entityId, const ComponentIndexType index)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING, "attempting to map component index with an invalid entity ID");
		return;
	}

	m_entityComponentIndexMap.map<ComponentType>(entityId, index);
}

template<typename ComponentType>
void EntityDatabase::unmapComponentIndex(const EntityId entityId)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING, "attempting to unmap component index with an invalid entity ID");
		return;
	}

	m_entityComponentIndexMap.unmap<ComponentType>(entityId);
}

template<typename ComponentType>
ComponentIndexType EntityDatabase::getMappedComponentIndex(const EntityId entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(EntityDatabase, LogLevel::NOTE_WARNING, "attempting to retrieve mapped component index with an invalid entity ID");
		return EntityComponentIndexMap::UNMAPPED_VALUE;
	}

	return m_entityComponentIndexMap.get<ComponentType>(entityId);
}

}// end namespace ve