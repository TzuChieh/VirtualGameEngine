#include "Entity.h"
#include "Resource/Component/Component.h"
#include "Resource/Scene.h"

using namespace xe;

Entity::Entity()
: m_scene(nullptr)
{

}

Entity::Entity(const EntityId entityId, Scene* scene)
: m_id(entityId), m_scene(scene)
{

}

void Entity::decompose()
{

}