#pragma once

#include "Common/type.h"
#include "ComponentHandle.h"
#include "Resource/Entity/Entity.h"

#include <memory>

namespace xe
{

class Engine;

typedef uint32 ComponentTypeId;

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
	// TODO: check ComponentType is actually derived from Component
	template<typename ComponentType>
	static ComponentTypeId getTypeId()
	{
		const static ComponentTypeId typeId = nextTypeId++;
		return typeId;
	}

private:
	static ComponentTypeId nextTypeId;
};

}