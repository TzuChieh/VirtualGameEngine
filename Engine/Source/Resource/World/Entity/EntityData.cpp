#include "EntityData.h"
#include "Entity.h"
#include "Resource/World/Component/Component.h"
#include "Resource/World/World.h"
#include "Core/Engine.h"

#include <iostream>

DEFINE_LOG_SENDER(EntityData);

namespace ve
{

EntityData::EntityData(const EntityId entityId, World* const parentWorld) :
	m_entityId(entityId), m_parentWorld(parentWorld)
{
	ENGINE_LOG_IF(parentWorld == nullptr, EntityData, LogLevel::NOTE_WARNING, "World is null");
}

EntityData::~EntityData()
{
	/*if(!m_parentWorld)
	{
		ENGINE_LOG(EntityData, LogLevel::NOTE_WARNING, "at dtor(), current entity does not belong to any world");
		return;
	}

	m_parentWorld->getEntityDatabase()->removeEntityData(m_entityId);*/
}

World* EntityData::getParentWorld() const
{
	return m_parentWorld;
}

EntityId EntityData::getEntityId() const
{
	return m_entityId;
}

}// end namespace ve