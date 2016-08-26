#include "Entity.h"
#include "Resource/Component/Component.h"
#include "Resource/Scene.h"
#include "Core/Engine.h"

#include <iostream>

using namespace ve;

const uint32 Entity::MAX_COMPONENTS;

Entity::Entity()
	: m_parentScene(nullptr)
{

}

Entity::Entity(const EntityIdentifier& entityIdentifier, Scene* parentScene)
	: m_entityIdentifier(entityIdentifier), m_parentScene(parentScene)
{

}

Entity::Entity(const Entity& other)
	: m_entityIdentifier(other.m_entityIdentifier), m_parentScene(other.m_parentScene)
{

}

void Entity::removeFromScene()
{
	if(!m_parentScene)
	{
		std::cerr << "Entity Warning: cannot remove since current entity does not belong to any scene" << std::endl;
		return;
	}

	m_parentScene->removeEntity(*this);
}

Scene* Entity::getParentScene() const
{
	return m_parentScene;
}

void Entity::setParentScene(Scene* parentScene)
{
	m_parentScene = parentScene;
}

EntityIdentifier Entity::getEntityIdentifier() const
{
	return m_entityIdentifier;
}

std::shared_ptr<ComponentHandle> Entity::getComponentHandleFromParentScene(ComponentTypeId typeId) const
{
	if(!m_parentScene)
	{
		std::cerr << "Entity Warning: cannot retrieve component since current entity does not belong to any scene" << std::endl;
		return nullptr;
	}

	return m_parentScene->getComponentHandle(*this, typeId);
}