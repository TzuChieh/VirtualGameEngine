#pragma once

#include "Resource/Component/ComponentManagerActionListener.h"

namespace xe
{

class StaticMeshGroupManagerActionListener : public ComponentManagerActionListener
{
public:
	StaticMeshGroupManagerActionListener();

	virtual void onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent) override;

private:

};

}