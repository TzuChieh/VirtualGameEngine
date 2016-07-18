#include "Scene.h"

#include <iostream>

using namespace xe;

Scene::Scene(const size_t initialEntityCapacity)
: m_entities(initialEntityCapacity), m_nextId(0U)
{
	std::cout << "Scene created with initial Entity capacity = " << initialEntityCapacity << std::endl;
}

Entity Scene::createEntity()
{
	EntityId id;

	if(m_availableEntityIds.empty())
	{
		id = m_nextId++;
	}
	else
	{
		id = m_availableEntityIds.back();
		m_availableEntityIds.pop_back();
	}

	return Entity(id, this);
}

void Scene::removeEntity(Entity&& entity)
{
	 
}