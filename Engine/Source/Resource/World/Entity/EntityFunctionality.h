#pragma once

#include "EntityId.h"
#include "Common/logging.h"
#include "Resource/World/World.h"

#include <memory>
#include <iostream>

DECLARE_LOG_SENDER_EXTERN(EntityFunctionality);

namespace ve
{

class Engine;
class Component;

class EntityFunctionality final
{

public:
	EntityFunctionality(EntityId entityId, World* parentWorld);
	~EntityFunctionality();

	// forbid copying
	EntityFunctionality(const EntityFunctionality& other) = delete;
	EntityFunctionality& operator = (const EntityFunctionality& rhs) = delete;

	World* getParentWorld() const;
	EntityId getEntityId() const;

	void setComponentParent(Component& component);

	template<typename ComponentType>
	void attachComponent(const ComponentType& component);

	template<typename ComponentType>
	ComponentType* getComponent();

	template<typename ComponentType>
	void detachComponent();

private:
	const EntityId m_entityId;
	World*   m_parentWorld;
};

// Templated method implementations:

template<typename ComponentType>
void EntityFunctionality::attachComponent(const ComponentType& component)
{
	m_parentWorld->attachComponent<ComponentType>(m_entityId, component);
}

template<typename ComponentType>
ComponentType* EntityFunctionality::getComponent()
{
	return m_parentWorld->getComponent<ComponentType>(m_entityId);
}

template<typename ComponentType>
void EntityFunctionality::detachComponent()
{
	m_parentWorld->detachComponent<ComponentType>(m_entityId);
}

}