#pragma once

#include "Entity.h"
#include "Resource/Component/Component.h"

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

	template<typename ComponentType>
	ComponentType* getComponent()
	{
		// TODO: check ComponentType is actually derived from Component

		Component* component = m_entityComponents[Component::getTypeId<ComponentType>()];
		if(component == nullptr)
		{
			std::cout << "EntityComponentStorage Warning: attempting to retrieve non-exist component" << std::endl;
			return;
		}

		return static_cast<ComponentType*>(component);
	}

private:
	std::array<Component*, static_cast<const size_t>(xe::EntityProperties::MAX_COMPONENTS)> m_entityComponents;
};

}