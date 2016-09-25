#pragma once

#include "Common/type.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"

#include <memory>
#include <cstddef>

DECLARE_LOG_SENDER_EXTERN(Entity);

namespace ve
{

class EntityData;
class World;
class EntityDatabase;

class Entity final
{
public:
	static const uint32 MAX_COMPONENTS = 64;

public:
	Entity();
	explicit Entity(EntityDatabase* const entityDatabase, const EntityId entityId);
	~Entity();

	//void removeFromWorld();

	inline EntityId getEntityId() const
	{
		return m_entityId;
	}

	EntityData*       operator -> ();
	const EntityData* operator -> () const;

private:
	EntityDatabase* m_entityDatabase;
	EntityId m_entityId;
};

}