#include "Entity.h"
#include "Resource/World/Entity/EntityData.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/World.h"
#include "Resource/World/EntityDatabase.h"

DEFINE_LOG_SENDER(Entity);

namespace ve
{

const uint32 Entity::MAX_COMPONENTS;

Entity::Entity(World* world) :
	m_entityData(nullptr)
{
	ENGINE_LOG_IF(world == nullptr, Entity, LogLevel::NOTE_WARNING, "World is null");

	m_entityData = world->getEntityDatabase()->createEntityData();
}

Entity::Entity(std::nullptr_t emptyWorld) : 
	m_entityData(emptyWorld)
{

}

Entity::Entity(const std::shared_ptr<EntityData>& entityData) :
	m_entityData(entityData)
{
	ENGINE_LOG_IF(entityData == nullptr, Entity, LogLevel::NOTE_WARNING, "entity data is null");
}

Entity::~Entity()
{
	if(m_entityData.unique())
	{
		// TODO: detach all components then remove entity
	}
}

void Entity::removeFromWorld()
{
	//EntityId id = m_functionality->getEntityId();
	//m_functionality->getParentWorld()->removeEntity(id);
}

EntityData* Entity::operator -> ()
{
	return m_entityData.get();
}

const EntityData* Entity::operator -> () const
{
	return m_entityData.get();
}

}// end namespace ve