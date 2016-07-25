#pragma once

#include "Common/type.h"

#include <vector>

namespace xe
{

template<typename ComponentType>
class TIndexedComponentManager
{
public:
	uint32 addComponent(const ComponentType& component)
	{
		uint32 index;

		if(m_availableIndices.empty())
		{
			index = m_components.size();
			m_components.push_back(component);
		}
		else
		{
			index = m_availableIndices.back();
			m_availableIndices.pop_back();
			m_components[index] = component;
		}

		return index;
	}

	virtual ComponentType* getComponent(uint32 index)
	{
		// TODO: check availability

		return &(m_components[index]);
	}

	virtual void removeComponent(uint32 index)
	{
		// TODO: check availability

		m_availableIndices.push_back(index);
	}

private:
	std::vector<ComponentType> m_components;
	std::vector<uint32> m_availableIndices;
};

}