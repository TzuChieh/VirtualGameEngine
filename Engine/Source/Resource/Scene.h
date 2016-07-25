#pragma once

#include "Resource/Entity/Entity.h"
#include "Resource/Entity/EntityIdentifier.h"
#include "Resource/Entity/EntityComponentStorage.h"

#include <vector>
#include <cstdint>

namespace xe
{

class Engine;
class Component;

class Scene
{
public:
	// Flush all pending components to the engine; components are ready to be used after
	// this call.
	void flush(Engine* engine);

	// Create & remove an entity.
	Entity createEntity();
	void removeEntity(Entity& entity);

	// Bind a component to an entity. The binded component can not be used until flushed.
	template<typename ComponentType>
	void bindComponent(const Entity& entity, const ComponentType& component)
	{
		// TODO: check ComponentType

		if(!isEntityValid(entity))
		{
			std::cerr << "Scene Warning: cannot bind component to an invalid entity" << std::endl;
			return;
		}

		std::unique_ptr<Component> pendingComponent(new ComponentType(component));
		pendingComponent->setParent(entity);
		m_pendingComponents.push_back(std::move(pendingComponent));
	}

	template<typename ComponentType>
	ComponentType* getComponent(const Entity& entity)
	{
		// TODO: check ComponentType

		if(!isEntityValid(entity))
		{
			std::cerr << "Scene Warning: cannot retrieve component for an invalid entity" << std::endl;
			return nullptr;
		}

		return m_entityComponents[entity.getEntityIdentifier().m_id].getComponent<ComponentType>();
	}

private:
	// Storage places for entities and their corresponding components.
	std::vector<Entity> m_entities;
	std::vector<EntityComponentStorage> m_entityComponents;

	// Mark the current state of each entity storage place by a serial number. If an entity's 
	// serial number does not match the valid one, it is corrupted and should not be used.
	std::vector<EntitySerial> m_validEntitySerials;

	// Every entity has an unique identifier. Here are identifiers thaty are ready for registration.
	std::vector<EntityIdentifier> m_availableEntityIdentifiers;

	// Components that are waiting to be flushed to engine.
	std::vector<std::unique_ptr<Component>> m_pendingComponents;

	// Check if an entity is valid to this scene.
	bool isEntityValid(const Entity& entity) const;
};

}