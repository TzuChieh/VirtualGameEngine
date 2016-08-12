#pragma once

#include "Resource/Component/types.h"
#include "Entity.h"
#include "Resource/Component/ComponentHandle.h"
#include "Common/logging.h"

#include <vector>
#include <array>
#include <iostream>

DECLARE_LOG_SENDER_EXTERN(EntityComponentHandleStorage);

namespace xe
{

class Component;

class EntityComponentHandleStorage
{
public:
	EntityComponentHandleStorage();

	void clear();
	void set(const std::shared_ptr<ComponentHandle>& componentHandle);

	std::shared_ptr<ComponentHandle> getComponentHandle(ComponentTypeId typeId) const
	{
		if(typeId >= Entity::MAX_COMPONENTS)
		{
			std::cout << "EntityComponentHandleStorage Warning: ComponentTypeId overflow" << std::endl;
			return nullptr;
		}

		return m_entityComponentHandles[typeId];
	}

private:
	std::array<std::shared_ptr<ComponentHandle>, Entity::MAX_COMPONENTS> m_entityComponentHandles;
};

}