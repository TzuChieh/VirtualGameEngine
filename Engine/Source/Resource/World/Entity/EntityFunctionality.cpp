#include "EntityFunctionality.h"
#include "Entity.h"
#include "Resource/World/Component/Component.h"
#include "Resource/World/World.h"
#include "Core/Engine.h"

#include <iostream>

DEFINE_LOG_SENDER(EntityFunctionality);

namespace ve
{

const uint32 Entity::MAX_COMPONENTS;

EntityFunctionality::EntityFunctionality(EntityId entityId, World* parentWorld) :
	m_entityId(entityId), m_parentWorld(parentWorld)
{
	ENGINE_LOG_IF(parentWorld == nullptr, EntityFunctionality, LogLevel::NOTE_WARNING, "World is null");
}

EntityFunctionality::~EntityFunctionality()
{
	if(!m_parentWorld)
	{
		ENGINE_LOG(EntityFunctionality, LogLevel::NOTE_WARNING, "at dtor(), current entity does not belong to any world");
		return;
	}

	m_parentWorld->getEntityDatabase()->removeEntityFunctionality(m_entityId);
}

void EntityFunctionality::setComponentParent(Component& component)
{
	component.setParent(Entity(m_parentWorld->getEntityDatabase()->getEntityFunctionality(m_entityId)));
}

World* EntityFunctionality::getParentWorld() const
{
	return m_parentWorld;
}

EntityId EntityFunctionality::getEntityId() const
{
	return m_entityId;
}

}// end namespace ve