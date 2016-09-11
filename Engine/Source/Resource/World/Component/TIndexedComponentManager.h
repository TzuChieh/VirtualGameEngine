#pragma once

#include "Common/type.h"
#include "TComponentManager.h"
#include "TTypedComponentHandle.h"

#include <vector>
#include <memory>
#include <iostream>

namespace ve
{

class Component;

template<typename ComponentType>
class TIndexedComponentManager : public TComponentManager<ComponentType>
{
public:
	std::shared_ptr<ComponentHandle> addComponent(const ComponentType& component);

	ComponentType* getComponent(uint32 index);
	void removeComponent(uint32 index);

	bool isIndexValid(uint32 index) const;
	uint32 storageSize() const;

	ComponentType& operator [] (const uint32 index);

private:
	std::vector<ComponentType> m_components;
	std::vector<uint32> m_availableIndices;
	std::vector<bool> m_componentValidity;
};

template<typename ComponentType>
class TIndexedComponentHandle final : public ComponentHandle
{

public:
	TIndexedComponentHandle(TIndexedComponentManager<ComponentType>* indexedComponentManager,
	                        uint32 componentIndex);
	~TIndexedComponentHandle() override = default;

	virtual Component* getComponent() override;
	virtual void removeComponent() override;

private:
	TIndexedComponentManager<ComponentType>* m_indexedComponentManager;
	uint32 m_componentIndex;
};

// TIndexedComponentManager implementation

template<typename ComponentType>
std::shared_ptr<ComponentHandle> ve::TIndexedComponentManager<ComponentType>::addComponent(const ComponentType& component)
{
	std::size_t index;

	if(m_availableIndices.empty())
	{
		index = m_components.size();
		m_components.push_back(component);
		m_componentValidity.push_back(true);
	}
	else
	{
		index = m_availableIndices.back();
		m_availableIndices.pop_back();
		m_components[index] = component;
		m_componentValidity[index] = true;
	}

	typedef ve::TTypedComponentHandle<ComponentType> TypedComponentHandle;

	std::shared_ptr<ComponentHandle> componentHandle = std::make_shared<TIndexedComponentHandle<ComponentType>>(this, static_cast<uint32>(index));
	std::shared_ptr<TypedComponentHandle> typedComponentHandle = std::make_shared<TypedComponentHandle>(componentHandle);
	notifyComponentAdded(typedComponentHandle);
	return componentHandle;
}

template<typename ComponentType>
ComponentType* ve::TIndexedComponentManager<ComponentType>::getComponent(uint32 index)
{
	if(!isIndexValid(index))
	{
		std::cerr << "TIndexedComponentManager Warning: at getComponent(), specified index overflow" << std::endl;
		return nullptr;
	}

	return &(m_components[index]);
}

template<typename ComponentType>
void ve::TIndexedComponentManager<ComponentType>::removeComponent(uint32 index)
{
	if(!isIndexValid(index)) 
	{
		std::cerr << "TIndexedComponentManager Warning: at removeComponent(), specified index overflow" << std::endl;
		return;
	}

	typedef TTypedComponentHandle<ComponentType> TypedComponentHandle;

	std::shared_ptr<ComponentHandle> componentHandle = std::make_shared<TIndexedComponentHandle<ComponentType>>(this, index);
	std::shared_ptr<TypedComponentHandle> typedComponentHandle = std::make_shared<TypedComponentHandle>(componentHandle);
	notifyComponentRemoval(typedComponentHandle);

	m_availableIndices.push_back(index);
	m_componentValidity[index] = false;
}

template<typename ComponentType>
bool ve::TIndexedComponentManager<ComponentType>::isIndexValid(uint32 index) const
{
	if(index < m_componentValidity.size())
	{
		if(m_componentValidity[index])
		{
			return true;
		}
	}

	return false;
}

template<typename ComponentType>
uint32 ve::TIndexedComponentManager<ComponentType>::storageSize() const
{
	return m_components.size();
}

template<typename ComponentType>
ComponentType& ve::TIndexedComponentManager<ComponentType>::operator [] (const uint32 index)
{
	return m_components[index];
}

// TIndexedComponentHandle implementation

template<typename ComponentType>
ve::TIndexedComponentHandle<ComponentType>::TIndexedComponentHandle(TIndexedComponentManager<ComponentType>* indexedComponentManager,
                                                                    uint32 componentIndex) : 
	m_indexedComponentManager(indexedComponentManager),
	m_componentIndex(componentIndex)
{

}

template<typename ComponentType>
ve::Component* ve::TIndexedComponentHandle<ComponentType>::getComponent()
{
	return static_cast<ve::Component*>(m_indexedComponentManager->getComponent(m_componentIndex));
}

template<typename ComponentType>
void ve::TIndexedComponentHandle<ComponentType>::removeComponent()
{
	m_indexedComponentManager->removeComponent(m_componentIndex);
}

}// end namespace xe
