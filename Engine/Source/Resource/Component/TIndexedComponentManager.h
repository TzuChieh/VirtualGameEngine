#pragma once

#include "Common/type.h"
#include "ComponentManager.h"
#include "ComponentHandle.h"

#include <vector>
#include <memory>
#include <iostream>

namespace xe
{

class Component;

template<typename ComponentType>
class TIndexedComponentManager : public ComponentManager
{
public:
	std::shared_ptr<ComponentHandle> addComponent(const ComponentType& component);

	ComponentType* getComponent(uint32 index);
	void removeComponent(uint32 index);

private:
	std::vector<ComponentType> m_components;
	std::vector<uint32> m_availableIndices;
};

template<typename ComponentType>
class TIndexedComponentHandle : public ComponentHandle
{
public:
	TIndexedComponentHandle(TIndexedComponentManager<ComponentType>* indexedComponentManager,
	                        uint32 componentIndex);

	virtual Component* getComponent() override;
	virtual void removeComponent() override;

private:
	TIndexedComponentManager<ComponentType>* m_indexedComponentManager;
	uint32 m_componentIndex;
};

// TIndexedComponentManager implementation

template<typename ComponentType>
std::shared_ptr<xe::ComponentHandle> xe::TIndexedComponentManager<ComponentType>::addComponent(const ComponentType& component)
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

	std::shared_ptr<xe::ComponentHandle> componentHandle = std::make_shared<xe::TIndexedComponentHandle<ComponentType>>(this, index);
	notifyComponentAdded(componentHandle);
	return componentHandle;
}

template<typename ComponentType>
ComponentType* xe::TIndexedComponentManager<ComponentType>::getComponent(uint32 index)
{
	// TODO: check availability

	return &(m_components[index]);
}

template<typename ComponentType>
void xe::TIndexedComponentManager<ComponentType>::removeComponent(uint32 index)
{
	// TODO: check availability

	notifyComponentRemoval(std::make_shared<xe::TIndexedComponentHandle<ComponentType>>(this, index));
	m_availableIndices.push_back(index);
}

// TIndexedComponentHandle implementation

template<typename ComponentType>
xe::TIndexedComponentHandle<ComponentType>::TIndexedComponentHandle(TIndexedComponentManager<ComponentType>* indexedComponentManager,
                                                                    uint32 componentIndex)
	: m_indexedComponentManager(indexedComponentManager),
	m_componentIndex(componentIndex)
{

}

template<typename ComponentType>
xe::Component* xe::TIndexedComponentHandle<ComponentType>::getComponent()
{
	return static_cast<xe::Component*>(m_indexedComponentManager->getComponent(m_componentIndex));
}

template<typename ComponentType>
void xe::TIndexedComponentHandle<ComponentType>::removeComponent()
{
	m_indexedComponentManager->removeComponent(m_componentIndex);
}

}// end namespace xe
