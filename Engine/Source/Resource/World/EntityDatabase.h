#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/Entity/EntityComponentIndexMap.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Resource/World/Entity/Entity.h"

#include <vector>
#include <functional>

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
	EntityData* getEntityData(const EntityId::IndexType& entityIndex);

	// Check if an entity ID is valid for current database.
	bool isEntityIdValid(const EntityId& entityId) const;

	// Map entity index to component indices.
	//
		template<typename ComponentType>
		void mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index);

		template<typename ComponentType>
		void unmapComponentIndex(const EntityId::IndexType entityIndex);

		template<typename ComponentType>
		ComponentIndexType getMappedComponentIndex(const EntityId::IndexType entityIndex) const;

	// forbid copying
	EntityDatabase(const EntityDatabase& other) = delete;
	EntityDatabase& operator = (const EntityDatabase& rhs) = delete;

private:
	World* m_parentWorld;

	std::vector<EntityId::SerialType> m_validEntitySerials;
	std::vector<EntityId> m_availableEntityIds;
	std::vector<EntityData> m_entityDataVector;

	std::vector<EntityData> m_test;

	EntityComponentIndexMap m_entityComponentIndexMap;
};

// Templated method implementations:

// Implementations:

template<typename ComponentType>
void EntityDatabase::mapComponentIndex(const EntityId::IndexType entityIndex, const ComponentIndexType index)
{
	m_entityComponentIndexMap.map<ComponentType>(entityIndex, index);
}

template<typename ComponentType>
void EntityDatabase::unmapComponentIndex(const EntityId::IndexType entityIndex)
{
	m_entityComponentIndexMap.unmap<ComponentType>(entityIndex);
}

template<typename ComponentType>
ComponentIndexType EntityDatabase::getMappedComponentIndex(const EntityId::IndexType entityIndex) const
{
	return m_entityComponentIndexMap.get<ComponentType>(entityIndex);
}

}// end namespace ve