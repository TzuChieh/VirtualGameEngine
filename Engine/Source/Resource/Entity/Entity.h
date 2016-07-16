#pragma once

#include "Common/type.h"

#include <unordered_map>
#include <typeinfo>
#include <vector>
#include <memory>

namespace xe
{

class Component;

class Entity
{
public:
	Entity();
	~Entity();

	void addComponent(std::unique_ptr<Component> component);

	inline Entity& operator = (const Entity* other)
	{
		// TODO
	}

protected:
	//virtual void update(float32 deltaS);

private:
	std::unordered_multimap<const std::type_info*, Component*> m_componentTypeMap;
	std::vector<Component*> m_components;
};

}