#pragma once

#include "ComponentHandle.h"

#include <memory>

namespace xe
{

class ComponentManagerActionListener
{
public:
	virtual void onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent) = 0;
	virtual void onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent) = 0;
};

}