#pragma once

#include "Common/type.h"
#include "Common/logging.h"

#include <memory>
#include <cstddef>

DECLARE_LOG_SENDER_EXTERN(Entity);

namespace ve
{

class EntityData;
class World;

class Entity final
{
public:
	static const uint32 MAX_COMPONENTS = 64;

public:
	explicit Entity(World* world);
	explicit Entity(std::nullptr_t emptyWorld);
	explicit Entity(const std::shared_ptr<EntityData>& entityData);
	~Entity();

	void removeFromWorld();

	EntityData*       operator -> ();
	const EntityData* operator -> () const;

private:
	std::shared_ptr<EntityData> m_entityData;
};

}