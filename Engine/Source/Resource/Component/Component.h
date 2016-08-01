#pragma once

#include "types.h"
#include "ComponentHandle.h"
#include "Resource/Entity/Entity.h"

#include <type_traits>
#include <memory>

namespace xe
{

class Engine;

class Component
{
public:
	Component();
	virtual ~Component() = 0;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) = 0;
	virtual ComponentTypeId getTypeId() = 0;

	Entity getParent();
	void setParent(const Entity& parent);

	/*inline Component& operator = (const Component& other)
	{
		
	}*/

private:
	Entity m_parent;

public:
	template<typename T, typename std::enable_if<std::is_base_of<Component, T>::value>::type* = nullptr>
	static ComponentTypeId getTypeId()
	{
		// TODO: check if T is derived from Component (not Component itself)

		const static ComponentTypeId typeId = nextTypeId++;
		return typeId;
	}

	// sinkhole
	template<typename T, typename std::enable_if<!(std::is_base_of<Component, T>::value)>::type* = nullptr>
	static ComponentTypeId getTypeId()
	{
		std::cout << "Component Warning: at getTypeId(), attempting to treat a non-Component type as a Component" << std::endl;
		return static_cast<ComponentTypeId>(Entity::MAX_COMPONENTS);
	}

private:
	static ComponentTypeId nextTypeId;
};

}