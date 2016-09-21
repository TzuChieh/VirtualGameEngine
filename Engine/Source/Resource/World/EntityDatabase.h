#pragma once

#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"

#include <vector>
#include <functional>
#include <memory>

DECLARE_LOG_SENDER_EXTERN(EntityDatabase);

namespace ve
{

class EntityFunctionality;
class World;

class EntityDatabase final
{
public:
	explicit EntityDatabase(World* const world);
	~EntityDatabase();

	// Create, remove and get an entity's functionality.
	std::shared_ptr<EntityFunctionality> createEntityFunctionality();
	void removeEntityFunctionality(const EntityId& entityId);
	std::shared_ptr<EntityFunctionality> getEntityFunctionality(const EntityId& entityId) const;

	// Check if an entity ID is valid for current database.
	bool isEntityIdValid(const EntityId& entityId) const;

	// forbid copying
	EntityDatabase(const EntityDatabase& other) = delete;
	EntityDatabase& operator = (const EntityDatabase& rhs) = delete;

private:
	World* m_parentWorld;

	std::vector<EntityId::SerialType> m_validEntitySerials;
	std::vector<EntityId> m_availableEntityIds;
	std::vector<std::shared_ptr<EntityFunctionality>> m_entityFunctionalities;

	
};

}// end namespace ve