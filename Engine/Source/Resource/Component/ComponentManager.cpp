#include "ComponentManager.h"

using namespace xe;

void ComponentManager::addActionListener(const std::shared_ptr<ComponentManagerActionListener>& actionListener)
{
	m_actionListeners.push_back(actionListener);
}

void ComponentManager::notifyComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	for(auto& actionListener : m_actionListeners)
	{
		actionListener->onComponentAdded(targetComponent);
	}
}

void ComponentManager::notifyComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	for(auto& actionListener : m_actionListeners)
	{
		actionListener->onComponentRemoval(targetComponent);
	}
}