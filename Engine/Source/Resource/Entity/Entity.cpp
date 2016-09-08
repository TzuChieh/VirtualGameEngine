#include "Entity.h"
#include "Resource/Component/Component.h"
#include "Resource/World.h"
#include "Core/Engine.h"

#include <iostream>

using namespace ve;

const uint32 Entity::MAX_COMPONENTS;

Entity::Entity() : 
	m_parentWorld(nullptr)
{

}

Entity::Entity(const EntityIdentifier& entityIdentifier, World* parentWorld) : 
	m_entityIdentifier(entityIdentifier), m_parentWorld(parentWorld)
{

}

Entity::Entity(const Entity& other)
	: m_entityIdentifier(other.m_entityIdentifier), m_parentWorld(other.m_parentWorld)
{

}

void Entity::removeFromWorld()
{
	if(!m_parentWorld)
	{
		std::cerr << "Entity Warning: cannot remove since current entity does not belong to any world" << std::endl;
		return;
	}

	m_parentWorld->removeEntity(*this);
}

World* Entity::getParentWorld() const
{
	return m_parentWorld;
}

void Entity::setParentWorld(World* parentWorld)
{
	m_parentWorld = parentWorld;
}

EntityIdentifier Entity::getEntityIdentifier() const
{
	return m_entityIdentifier;
}

std::shared_ptr<ComponentHandle> Entity::getComponentHandleFromParentWorld(ComponentTypeId typeId) const
{
	if(!m_parentWorld)
	{
		std::cerr << "Entity Warning: cannot retrieve component since current entity does not belong to any world" << std::endl;
		return nullptr;
	}

	return m_parentWorld->getComponentHandle(*this, typeId);
}