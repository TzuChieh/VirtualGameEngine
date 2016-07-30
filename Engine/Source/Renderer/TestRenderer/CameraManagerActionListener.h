#pragma once

#include "Resource/Component/ComponentManagerActionListener.h"

namespace xe
{

class CameraManagerActionListener : public ComponentManagerActionListener
{
public:
	virtual void onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent) override;
};

}