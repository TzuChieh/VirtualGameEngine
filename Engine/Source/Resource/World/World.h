#pragma once

#include "Resource/World/Component/Component.h"
#include "Resource/World/Component/ComponentIndexType.h"
#include "Common/logging.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/ComponentDatabase.h"
#include "Resource/World/Event/TComponentListener.h"
#include "Resource/World/Event/TComponentListenerContainer.h"
#include "Resource/World/Component/TComponentHandle.h"

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

	ComponentDatabase* getComponentDatabase();

	// Attach a component to an entity. The attached component can not be used until flushed.
	template<typename ComponentType>
	void attachComponent(const EntityId& entityId, const ComponentType& component);

	template<typename ComponentType>
	void detachComponent(const EntityId& entityId);

	template<typename ComponentType>
	ComponentType* getComponent(const EntityId& entityId);

	template<typename ComponentType>
	TComponentHandle<ComponentType> getComponentHandle(const EntityId& entityId) const;

	template<typename ComponentType>
	void addComponentListener(TComponentListener<ComponentType>* listener) const;

	template<typename ComponentType>
	void removeComponentListener(TComponentListener<ComponentType>* listener) const;

private:
	// Mark the current state of each entity storage place by a serial number. If an entity's 
	// serial number does not match the valid one, it is corrupted and should not be used.
	std::vector<EntityId::SerialType> m_validEntitySerials;

	// Every entity has an unique ID. Here are ID's that are ready for registration.
	std::vector<EntityId> m_availableEntityIds;

	std::vector<std::function<void()>> m_componentAttachers;
	std::vector<std::function<void()>> m_componentDetachers;

	std::vector<std::shared_ptr<EntityFunctionality>> m_entityFunctionalities;


	ComponentDatabase m_componentDatabase;

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
			ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot attach component to an invalid EntityId");
			return;
		}

		const ComponentIndexType componentIndex = m_componentDatabase.addComponent(component);
		m_componentDatabase.mapComponentIndex<ComponentType>(entityId.m_index, componentIndex);

		ComponentType* componentFromDatabase = &(m_componentDatabase.getComponent<ComponentType>(componentIndex));
		componentFromDatabase->setParent(Entity(getEntityFunctionality(entityId)));
		TComponentListenerContainer<ComponentType>::notifyAllOnComponentAdded(componentFromDatabase, componentIndex);
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
			ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot detach component from an invalid EntityId");
			return;
		}

		const ComponentIndexType componentIndex = m_componentDatabase.getMappedComponentIndex<ComponentType>(entityId.m_index);

		if(componentIndex < 0)
		{
			ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot detach non-exist component");
			return;
		}

		// Here we should be sure that the ID and the component index are both valid.

		ComponentType* componentFromDatabase = &(m_componentDatabase.getComponent<ComponentType>(componentIndex));
		TComponentListenerContainer<ComponentType>::notifyAllOnComponentRemoval(componentFromDatabase, componentIndex);

		m_componentDatabase.removeComponent<ComponentType>(componentIndex);
		m_componentDatabase.unmapComponentIndex<ComponentType>(entityId.m_index);
	};

	m_componentDetachers.push_back(componentDetacher);
}

template<typename ComponentType>
ComponentType* World::getComponent(const EntityId& entityId)
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot get component from an invalid EntityId");
		return nullptr;
	}

	const ComponentIndexType componentIndex = m_componentDatabase.getMappedComponentIndex<ComponentType>(entityId.m_index);

	if(componentIndex < 0)
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot get non-exist component");
		return nullptr;
	}

	return &(m_componentDatabase.getComponent<ComponentType>(componentIndex));
}

template<typename ComponentType>
TComponentHandle<ComponentType> World::getComponentHandle(const EntityId& entityId) const
{
	if(!isEntityIdValid(entityId))
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot get component handle from an invalid EntityId");
		return TComponentHandle<ComponentType>();
	}

	const ComponentIndexType componentIndex = m_componentDatabase.getMappedComponentIndex<ComponentType>(entityId.m_index);

	if(componentIndex < 0)
	{
		ENGINE_LOG(World, LogLevel::NOTE_WARNING, "cannot get non-exist component");
		return TComponentHandle<ComponentType>();
	}

	return m_componentDatabase.getComponentHandle<ComponentType>(componentIndex);
}

template<typename ComponentType>
void World::addComponentListener(TComponentListener<ComponentType>* listener) const
{
	TComponentListenerContainer<ComponentType>::addListener(listener);
}

template<typename ComponentType>
void World::removeComponentListener(TComponentListener<ComponentType>* listener) const
{
	TComponentListenerContainer<ComponentType>::removeListener(listener);
}

}// end namespace ve