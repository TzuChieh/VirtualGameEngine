#pragma once

#include "Resource/Entity/Entity.h"
#include "Resource/Entity/EntityIdentifier.h"

#include <vector>
#include <cstdint>

namespace xe
{
class Engine;
class Component;

class Scene
{
public:
	Scene(const size_t initialEntityCapacity);

	// process all pending actions
	void flush(Engine* engine);

	Entity createEntity();
	void removeEntity(Entity& entity);

private:
	std::vector<Entity> m_entities;
	
	std::vector<EntitySerial> m_validEntitySerials;
	std::vector<EntityIdentifier> m_availableEntityIdentifiers;

	// TODO: pending Components (add to engine)
};

}