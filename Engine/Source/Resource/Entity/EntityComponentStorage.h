#pragma once

#include "Common/type.h"
#include "Entity.h"
#include "Resource/Component/Component.h"
#include "Resource/Component/ComponentHandle.h"

#include <vector>
#include <array>
#include <iostream>

namespace xe
{

class Component;

class EntityComponentStorage
{
public:
	EntityComponentStorage();

	void clear();
	void set(uint32 index, std::shared_ptr<ComponentHandle> componentHandle);

	template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
	inline T* getComponent() const
	{
		// TODO: check if T is derived from Component (not Component itself)

		auto& componentHandle = m_entityComponentHandles[Component::getTypeId<T>()];
		if(componentHandle == nullptr)
		{
			std::cout << "EntityComponentStorage Warning: attempting to retrieve non-exist component" << std::endl;
		}
		
		return static_cast<T*>(componentHandle->getComponent());
	}

	// sinkhole
	template<typename T, typename std::enable_if<!(std::is_base_of<Component, T>::value)>::type* = nullptr>
	inline T* getComponent() const
	{
		std::cout << "ComponentHandle Warning: attempting to treat a non-Component type as a Component" << std::endl;
		return nullptr;
	}

private:
	std::array<std::shared_ptr<ComponentHandle>, 
	           static_cast<const size_t>(xe::EntityProperties::MAX_COMPONENTS)> m_entityComponentHandles;
};

}