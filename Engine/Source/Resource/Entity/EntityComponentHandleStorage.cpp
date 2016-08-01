#include "EntityComponentHandleStorage.h"
#include "Resource/Component/Component.h"

using namespace xe;

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
		std::cout << "EntityComponentHandleStorage Warning: at set(), component handle is empty" << std::endl;
		return;
	}

	const ComponentTypeId typeId = componentHandle->getComponent()->getTypeId();
	if(typeId >= Entity::MAX_COMPONENTS)
	{
		std::cout << "EntityComponentHandleStorage Warning: ComponentTypeId overflow" << std::endl;
		return;
	}

	m_entityComponentHandles[typeId] = componentHandle;
}

