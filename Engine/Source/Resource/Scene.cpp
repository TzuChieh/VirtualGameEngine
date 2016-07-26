#include "Scene.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace xe;

Scene::Scene(Engine* engine)
	: m_engine(engine)
{

}

void Scene::flush()
{
	for(int32 i = m_pendingComponents.size() - 1; i >= 0; i--)
	{
		auto& pendingComponent = m_pendingComponents[i];
		auto& componentHandle = pendingComponent->addToEngine(m_engine);
		EntityId entityId = pendingComponent->getParent().getEntityIdentifier().m_id;

		m_entityComponents[entityId].set(pendingComponent->getTypeId(), componentHandle);
		m_pendingComponents.pop_back();
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
		m_entityComponents.push_back(EntityComponentStorage());
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
	if(entity.getParentScene() != this)
	{
		std::cerr << "Scene Warning: cannot remove an entity that does not belong to current scene" << std::endl;
		return;
	}

	// generate a new EntityIdentifier and store it for later use
	EntityIdentifier newEntityIdentifier(entity.getEntityIdentifier());
	newEntityIdentifier.m_serial++;
	m_availableEntityIdentifiers.push_back(newEntityIdentifier);
	m_validEntitySerials[newEntityIdentifier.m_id] = newEntityIdentifier.m_serial;
	m_entityComponents[newEntityIdentifier.m_id].clear();

	entity.setParentScene(nullptr);
}

bool Scene::isEntityValid(const Entity& entity) const
{
	if(entity.getParentScene() != this)
	{
		std::cerr << "Scene Warning: entity doesn't belong to current scene" << std::endl;
		return false;
	}

	const EntityIdentifier& entityIdentifier = entity.getEntityIdentifier();
	if(entityIdentifier.m_id < m_validEntitySerials.size())
	{
		if(m_validEntitySerials[entityIdentifier.m_id] != entityIdentifier.m_serial)
		{
			std::cerr << "Scene Warning: entity serial is invalid" << std::endl;
			return false;
		}
	}
	else
	{
		std::cerr << "Scene Warning: entity id is not valid" << std::endl;
		return false;
	}

	return true;
}