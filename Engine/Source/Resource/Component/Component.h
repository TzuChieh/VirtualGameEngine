#pragma once

#include "Common/type.h"

namespace xe
{

class Engine;
class ComponentHandle;

typedef uint32 ComponentTypeId;

class Component
{
public:
	Component();
	virtual ~Component() = 0;

	virtual void update(float32 deltaS) = 0;
	virtual void addToEngine(Engine* engine) = 0;

	inline ComponentHandle* getComponentHandle() const
	{
		return m_componentHandle;
	}

	inline Component& operator = (const Component& other)
	{
		
	}

private:
	ComponentHandle* m_componentHandle;

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