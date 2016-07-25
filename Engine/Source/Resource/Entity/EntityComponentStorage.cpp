#include "EntityComponentStorage.h"

using namespace xe;

EntityComponentStorage::EntityComponentStorage()
{
	clear();
}

void EntityComponentStorage::clear()
{
	for(auto& component : m_entityComponentHandles)
	{
		component.reset();
	}
}

void EntityComponentStorage::set(uint32 index, std::shared_ptr<ComponentHandle> componentHandle)
{
	m_entityComponentHandles[index] = componentHandle;
}

