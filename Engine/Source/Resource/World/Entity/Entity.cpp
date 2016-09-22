#include "Entity.h"
#include "Resource/World/Entity/EntityFunctionality.h"
#include "Resource/World/Entity/EntityId.h"
#include "Resource/World/World.h"
#include "Resource/World/EntityDatabase.h"

DEFINE_LOG_SENDER(Entity);

namespace ve
{

const uint32 Entity::MAX_COMPONENTS;

Entity::Entity(World* world) :
	m_functionality(nullptr)
{
	ENGINE_LOG_IF(world == nullptr, Entity, LogLevel::NOTE_WARNING, "World is null");

	m_functionality = world->getEntityDatabase()->createEntityFunctionality();
}

Entity::Entity(std::nullptr_t emptyWorld) : 
	m_functionality(emptyWorld)
{

}

Entity::Entity(const std::shared_ptr<EntityFunctionality>& functionality) : 
	m_functionality(functionality)
{
	ENGINE_LOG_IF(functionality == nullptr, Entity, LogLevel::NOTE_WARNING, "functionality is null");
}

Entity::~Entity()
{
	if(m_functionality.unique())
	{
		// TODO: detach all components then remove entity
	}
}

void Entity::removeFromWorld()
{
	//EntityId id = m_functionality->getEntityId();
	//m_functionality->getParentWorld()->removeEntity(id);
}

EntityFunctionality* Entity::operator -> ()
{
	return m_functionality.get();
}

const EntityFunctionality* Entity::operator -> () const
{
	return m_functionality.get();
}

}// end namespace ve