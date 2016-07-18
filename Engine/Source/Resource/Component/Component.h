#pragma once

#include "Common/type.h"

namespace xe
{

class Engine;
class ComponentController;

typedef uint32 ComponentTypeId;

class Component
{
public:
	Component();
	virtual ~Component() = 0;

	virtual void update(float32 deltaS) = 0;
	virtual void addToEngine(Engine* engine) = 0;

	inline Component& operator = (const Component& other)
	{
		m_componentController = other.m_componentController;
	}

private:
	ComponentController* m_componentController;

private:
	static ComponentTypeId nextTypeId;

	template<typename ComponentType>
	static ComponentTypeId getTypeId()
	{
		const static ComponentTypeId typeId = nextTypeId++;
		return typeId;
	}
};

}