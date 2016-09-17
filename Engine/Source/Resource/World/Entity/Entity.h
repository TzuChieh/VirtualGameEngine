#pragma once

#include "Common/type.h"
#include "Common/logging.h"

#include <memory>
#include <cstddef>

DECLARE_LOG_SENDER_EXTERN(Entity);

namespace ve
{

class EntityFunctionality;
class World;

class Entity final
{
public:
	static const uint32 MAX_COMPONENTS = 64;

public:
	explicit Entity(World* world);
	explicit Entity(std::nullptr_t emptyWorld);
	explicit Entity(const std::shared_ptr<EntityFunctionality>& functionality);
	~Entity();

	void removeFromWorld();

	EntityFunctionality*       operator -> ();
	const EntityFunctionality* operator -> () const;

private:
	std::shared_ptr<EntityFunctionality> m_functionality;
};

}