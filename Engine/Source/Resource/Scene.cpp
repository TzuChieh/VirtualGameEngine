#include "Scene.h"
#include "Resource/Component/Component.h"
#include "Resource/Entity/Entity.h"

#include <iostream>

DEFINE_LOG_SENDER(Scene);

using namespace xe;

Scene::Scene(Engine* engine) :
	m_engine(engine)
{

}

void Scene::flush()
{
	// TODO: get rid of pop_back and flush with expected order

	for(int32 i = m_pendingComponents.size() - 1; i >= 0; i--)
	{
		const auto& pendingComponent = m_pendingComponents[i];
		const auto& componentHandle = pendingComponent->addToEngine(m_engine);
		EntityId entityId = pendingComponent->getParent().getEntityIdentifier().m_id;

		m_entityComponentHandles[entityId].set(componentHandle);
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
		m_entityComponentHandles.push_back(EntityComponentHandleStorage());
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
		ENGINE_LOG(Scene, LogLevel::NOTE_WARNING,
		           "cannot remove an entity that does not belong to current scene");
		return;
	}

	// generate a new EntityIdentifier and store it for later use
	EntityIdentifier newEntityIdentifier(entity.getEntityIdentifier());
	newEntityIdentifier.m_serial++;
	m_availableEntityIdentifiers.push_back(newEntityIdentifier);
	m_validEntitySerials[newEntityIdentifier.m_id] = newEntityIdentifier.m_serial;
	m_entityComponentHandles[newEntityIdentifier.m_id].clear();

	entity.setParentScene(nullptr);
}

std::shared_ptr<ComponentHandle> Scene::getComponentHandle(const Entity& entity, ComponentTypeId typeId) const
{
	if(!isEntityValid(entity))
	{
		ENGINE_LOG(Scene, LogLevel::NOTE_WARNING,
		           "cannot retrieve component handle for an invalid entity");
		return nullptr;
	}

	return m_entityComponentHandles[getEntityStorageIndex(entity)].getComponentHandle(typeId);
}

bool Scene::isEntityValid(const Entity& entity) const
{
	if(entity.getParentScene() != this)
	{
		ENGINE_LOG(Scene, LogLevel::NOTE_WARNING,
		           "invalid entity detected - entity doesn't belong to current scene");
		return false;
	}

	const EntityIdentifier& entityIdentifier = entity.getEntityIdentifier();
	if(entityIdentifier.m_id < m_validEntitySerials.size())
	{
		if(m_validEntitySerials[entityIdentifier.m_id] != entityIdentifier.m_serial)
		{
			ENGINE_LOG(Scene, LogLevel::NOTE_WARNING,
			           "invalid entity detected - entity serial is invalid");
			return false;
		}
	}
	else
	{
		ENGINE_LOG(Scene, LogLevel::NOTE_WARNING,
		           "invalid entity detected - entity id is invalid");
		return false;
	}

	return true;
}

EntityId Scene::getEntityStorageIndex(const Entity& entity) const
{
	return entity.getEntityIdentifier().m_id;
}