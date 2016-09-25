#pragma once

#include "EntityId.h"
#include "Common/logging.h"
#include "Resource/World/World.h"
#include "Resource/World/Component/TComponentHandle.h"

#include <memory>
#include <iostream>

DECLARE_LOG_SENDER_EXTERN(EntityData);

namespace ve
{

class Engine;
class Component;

class EntityData final
{

public:
	EntityData(const EntityId entityId, World* const parentWorld);
	~EntityData();

	// forbid copying
	//EntityFunctionality(const EntityFunctionality& other) = delete;
	//EntityFunctionality& operator = (const EntityFunctionality& rhs) = delete;

	World* getParentWorld() const;
	EntityId getEntityId() const;

	template<typename ComponentType>
	void attachComponent(const ComponentType& component);

	template<typename ComponentType>
	ComponentType* getComponent();

	template<typename ComponentType>
	TComponentHandle<ComponentType> getComponentHandle() const;

	template<typename ComponentType>
	void detachComponent();

private:
	EntityId m_entityId;
	World* m_parentWorld;
};

// Templated method implementations:

template<typename ComponentType>
void EntityData::attachComponent(const ComponentType& component)
{
	m_parentWorld->attachComponent<ComponentType>(m_entityId, component);
}

template<typename ComponentType>
ComponentType* EntityData::getComponent()
{
	return m_parentWorld->getComponent<ComponentType>(m_entityId);
}

template<typename ComponentType>
TComponentHandle<ComponentType> EntityData::getComponentHandle() const
{
	return m_parentWorld->getComponentHandle<ComponentType>(m_entityId);
}

template<typename ComponentType>
void EntityData::detachComponent()
{
	m_parentWorld->detachComponent<ComponentType>(m_entityId);
}

}// end namespace ve