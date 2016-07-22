#pragma once

#include "TComponentManager.h"
#include "Common/type.h"

#include <vector>

namespace xe
{

template<typename ComponentType>
class TContinuousMemoryComponentManager : public TComponentManager<ComponentType>
{
public:
	virtual void updateComponents(float32 deltaS) override
	{
		for(uint32 i = 0; i < m_components.size(); i++)
		{
			//m_components[i].update(deltaS);
		}
	}

	virtual void addComponent(ComponentType&& component) override
	{
		m_components.push_back(std::move(component));
	}

private:
	std::vector<ComponentType> m_components;
};

}