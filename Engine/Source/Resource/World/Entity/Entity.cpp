#include "Entity.h"
#include "Resource/World/Entity/EntityData.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/World.h"
#include "Resource/World/EntityDatabase.h"

DEFINE_LOG_SENDER(Entity);

namespace ve
{

const uint32 Entity::MAX_COMPONENTS;

Entity::Entity() :
	m_entityDatabase(nullptr), m_entityId(0)
{

}

Entity::Entity(EntityDatabase* const entityDatabase, const EntityId entityId) :
	m_entityDatabase(entityDatabase), m_entityId(entityId)
{
	ENGINE_LOG_IF(entityDatabase == nullptr, Entity, LogLevel::NOTE_WARNING, "EntityDatabase is null");
}

Entity::~Entity()
{
	//if(m_entityData.unique())
	//{
	//	// TODO: detach all components then remove entity
	//}
}

//void Entity::removeFromWorld()
//{
//	//EntityId id = m_functionality->getEntityId();
//	//m_functionality->getParentWorld()->removeEntity(id);
//}

EntityData* Entity::operator -> ()
{
	return m_entityDatabase->getEntityData(m_entityId);
}

const EntityData* Entity::operator -> () const
{
	return m_entityDatabase->getEntityData(m_entityId);
}

}// end namespace ve