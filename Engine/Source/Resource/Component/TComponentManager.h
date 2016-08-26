#pragma once

#include "TComponentManagerActionListener.h"
#include "TTypedComponentHandle.h"

#include <memory>
#include <vector>

namespace ve
{

template<typename ComponentType>
class TComponentManager
{
public:
	void addActionListener(const std::shared_ptr<TComponentManagerActionListener<ComponentType>>& actionListener);

protected:
	void notifyComponentAdded(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent);
	void notifyComponentRemoval(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent);

private:
	std::vector<std::shared_ptr<TComponentManagerActionListener<ComponentType>>> m_actionListeners;
};

}

// implementation

template<typename ComponentType>
void ve::TComponentManager<ComponentType>::addActionListener(const std::shared_ptr<TComponentManagerActionListener<ComponentType>>& actionListener)
{
	m_actionListeners.push_back(actionListener);
}

template<typename ComponentType>
void ve::TComponentManager<ComponentType>::notifyComponentAdded(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent)
{
	for(auto& actionListener : m_actionListeners)
	{
		actionListener->onComponentAdded(targetComponent);
	}
}

template<typename ComponentType>
void ve::TComponentManager<ComponentType>::notifyComponentRemoval(const std::shared_ptr<TTypedComponentHandle<ComponentType>>& targetComponent)
{
	for(auto& actionListener : m_actionListeners)
	{
		actionListener->onComponentRemoval(targetComponent);
	}
}