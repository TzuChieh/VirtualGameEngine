#include "EntityComponentHandleStorage.h"
#include "Resource/Component/Component.h"

DEFINE_LOG_SENDER(EntityComponentHandleStorage);

using namespace ve;

EntityComponentHandleStorage::EntityComponentHandleStorage()
{
	clear();
}

void EntityComponentHandleStorage::clear()
{
	for(auto& component : m_entityComponentHandles)
	{
		component.reset();
	}
}

void EntityComponentHandleStorage::set(const std::shared_ptr<ComponentHandle>& componentHandle)
{
	if(!componentHandle)
	{
		ENGINE_LOG(EntityComponentHandleStorage, LogLevel::NOTE_WARNING,
		           "at set(), component handle is empty");
		return;
	}

	const ComponentTypeId typeId = componentHandle->getComponent()->getTypeId();
	if(typeId >= Entity::MAX_COMPONENTS)
	{
		ENGINE_LOG(EntityComponentHandleStorage, LogLevel::NOTE_WARNING,
		           "at set(), ComponentTypeId overflow");
		return;
	}

	m_entityComponentHandles[typeId] = componentHandle;
}

