#pragma once

#include "ComponentHandle.h"
#include "ComponentManagerActionListener.h"

#include <memory>
#include <vector>

namespace xe
{

class ComponentManager
{
public:
	void addActionListener(const std::shared_ptr<ComponentManagerActionListener>& actionListener);

protected:
	void notifyComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent);
	void notifyComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent);

private:
	std::vector<std::shared_ptr<ComponentManagerActionListener>> m_actionListeners;
};

}