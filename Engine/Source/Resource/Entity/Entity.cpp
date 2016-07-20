#include "Entity.h"
#include "Resource/Component/Component.h"
#include "Resource/Scene.h"
#include "Core/Engine.h"

#include <iostream>

using namespace xe;

Entity::Entity()
	: m_scene(nullptr)
{

}

Entity::Entity(const EntityIdentifier& entityIdentifier, Scene* scene)
	: m_entityIdentifier(entityIdentifier), m_scene(scene)
{

}

void Entity::removeFromScene()
{
	if(!m_scene)
	{
		std::cerr << "Entity Warning: cannot remove since current entity does not belong to any scene" << std::endl;
		return;
	}

	m_scene->removeEntity(*this);
}