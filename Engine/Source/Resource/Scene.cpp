#include "Scene.h"

#include <iostream>

using namespace xe;

Scene::Scene(const size_t initialEntityCapacity)
	: m_entities(initialEntityCapacity), m_validEntitySerials(initialEntityCapacity)
{
	std::cout << "Scene created with initial Entity capacity = " << initialEntityCapacity << std::endl;
}

void Scene::flush(Engine* engine)
{
	for(uint32 i = 0; i < m_entities.size(); i++)
	{
		// check if the i-th entity is valid for use
		if(m_validEntitySerials[i] != EntityIdentifier::invalidSerial)
		{
			m_entities[i].addToEngine(engine);
		}
	}
}

Entity Scene::createEntity()
{
	Entity entity;

	if(m_availableEntityIdentifiers.empty())
	{
		EntityIdentifier entityIdentifier(m_entities.size(), EntityIdentifier::invalidSerial + 1);
		
		entity = Entity(entityIdentifier, this);
		m_entities.push_back(entity);
		m_validEntitySerials.push_back(entityIdentifier.m_serial);
	}
	else
	{
		EntityIdentifier entityIdentifier = m_availableEntityIdentifiers.back();
		m_availableEntityIdentifiers.pop_back();

		entity = Entity(entityIdentifier, this);
		m_entities[entityIdentifier.m_id] = entity;
		m_validEntitySerials[entityIdentifier.m_id] = entityIdentifier.m_serial;
	}

	return entity;
}

void Scene::removeEntity(Entity& entity)
{
	if(entity.m_scene != this)
	{
		std::cerr << "Scene Warning: cannot remove an entity that does not belong to current scene" << std::endl;
		return;
	}

	// generate a new EntityIdentifier and store it for later use
	EntityIdentifier newEntityIdentifier(entity.m_entityIdentifier);
	newEntityIdentifier.m_serial++;
	m_availableEntityIdentifiers.push_back(newEntityIdentifier);
	m_validEntitySerials[newEntityIdentifier.m_id] = EntityIdentifier::invalidSerial;

	entity.m_scene = nullptr;
}