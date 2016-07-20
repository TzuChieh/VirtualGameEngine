#pragma once

#include "Common/type.h"

#include <iostream>
#include <type_traits>

namespace xe
{

class Component;
typedef uint64 ComponentId;

class ComponentHandle
{
public:
	ComponentHandle()
		: m_component(nullptr)
	{

	}

	ComponentHandle(Component* component)
		: m_component(component)
	{

	}

	template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
	inline T* getComponent() const
	{
		std::cout << "getComponent() executed" << std::endl;
		return static_cast<T*>(m_component);
	}

	// sinkhole
	template<typename T, typename std::enable_if<!(std::is_base_of<Component, T>::value)>::type* = nullptr>
	inline T* getComponent() const
	{
		std::cout << "ComponentHandle Warning: attempting to treat a non-Component type as a Component" << std::endl;
		return nullptr;
	}

private:
	Component* m_component;
};

}