#pragma once

#include "Resource/World/Component/Component.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/EntityComponentDatabase.h"

#include <vector>
#include <cstdint>
#include <memory>
#include <functional>

DECLARE_LOG_SENDER_EXTERN(World);

namespace ve
{

class Component;
class Entity;
class ComponentHandle;
class Engine;
class EntityFunctionality;

class World final
{
public:
	World(Engine* engine);

	// forbid copying
	World(const World& other) = delete;
	World& operator = (const World& rhs) = delete;

	bool init();

	// Flush all pending components to the engine; components will be ready after this call.
	void flushAttachings();
	void flushDetachings();

	// Create, remove and get an entity's functionality.
	std::shared_ptr<EntityFunctionality> createEntityFunctionality();
	void removeEntityFunctionality(const EntityId& entityId);
	std::shared_ptr<EntityFunctionality> getEntityFunctionality(const EntityId& entityId) const;

	EntityComponentDatabase* getEntityComponentDatabase();

	// Attach a component to an entity. The attached component can not be used until flushed.
	template<typename ComponentType>
	void attachComponent(const EntityId& entityId, const ComponentType& component);

	template<typename ComponentType>
	void detachComponent(const EntityId& entityId);

	template<typename ComponentType>
	ComponentType* getComponent(const EntityId& entityId);

private:
	// Mark the current state of each entity storage place by a serial number. If an entity's 
	// serial number does not match the valid one, it is corrupted and should not be used.
	std::vector<EntityId::SerialType> m_validEntitySerials;

	// Every entity has an unique ID. Here are ID's that are ready for registration.
	std::vector<EntityId> m_availableEntityIds;

	std::vector<std::function<void()>> m_componentAttachers;
	std::vector<std::function<void()>> m_componentDetachers;

	std::vector<std::shared_ptr<EntityFunctionality>> m_entityFunctionalities;


	EntityComponentDatabase m_entityComponentDatabase;

	Engine* m_engine;

	// Check if an entity is valid to this world.
	bool isEntityIdValid(const EntityId& entityId) const;

	EntityId::IndexType getEntityIndex(const Entity& entity) const;
	bool allocateStorageForCoreComponentTypes();
};

// Templated method implementations:

template<typename ComponentType>
void World::attachComponent(const EntityId& entityId, const ComponentType& component)
{
	const auto& componentAttacher = [entityId, component, this]() -> void
	{
		if(!isEntityIdValid(entityId))
		{
			std::cerr << "World Warning: cannot attach component to an invalid EntityId" << std::endl;
			return;
		}

		const ComponentIndexType componentIndex = m_entityComponentDatabase.addComponent(component);
		m_entityComponentDatabase.mapComponentIndex<ComponentType>(entityId.m_index, componentIndex);
	};
	m_componentAttachers.push_back(componentAttacher);
}

template<typename ComponentType>
void World::detachComponent(const EntityId& entityId)
{
	const auto& componentDetacher = [entityId, this]() -> void
	{
		if(!isEntityIdValid(entityId))
		{
			std::cerr << "World Warning: cannot detach component from an invalid EntityId" << std::endl;
			return;
		}

		const ComponentIndexType componentIndex = m_entityComponentDatabase.getMappedComponentIndex<ComponentType>(entityId.m_index);

		if(componentIndex < 0)
		{
			std::cerr << "World Warning: cannot detach non-exist component" << std::endl;
			return;
		}

		m_entityComponentDatabase.removeComponent<ComponentType>(componentIndex);
		m_entityComponentDatabase.unmapComponentIndex<ComponentIndexType>(entityId.m_index, componentIndex);
	};
	m_componentDetachers.push_back(componentDetacher);
}

template<typename ComponentType>
ComponentType* World::getComponent(const EntityId& entityId)
{
	if(!isEntityIdValid(entityId))
	{
		std::cerr << "World Warning: cannot get component from an invalid EntityId" << std::endl;
		return nullptr;
	}

	const ComponentIndexType componentIndex = m_entityComponentDatabase.getMappedComponentIndex<ComponentType>(entityId.m_index);

	if(componentIndex < 0)
	{
		std::cerr << "World Warning: cannot get non-exist component" << std::endl;
		return nullptr;
	}

	return &(m_entityComponentDatabase.getComponent<ComponentType>(componentIndex));
}

}