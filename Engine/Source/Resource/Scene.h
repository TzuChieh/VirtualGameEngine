#pragma once

#include "Resource/Entity/Entity.h"

#include <vector>

namespace xe
{

class Scene
{
public:
	Scene(const size_t initialEntityCapacity);

	Entity createEntity();
	void removeEntity(Entity&& entity);

private:
	std::vector<Entity> m_entities;
	std::vector<EntityId> m_availableEntityIds;

	EntityId m_nextId;
};

}