#pragma once

#include "Resource/Component/ComponentManagerActionListener.h"

namespace xe
{

class StaticRenderableContainer;

class StaticModelGroupManagerActionListener : public ComponentManagerActionListener
{
public:
	StaticModelGroupManagerActionListener(StaticRenderableContainer* staticRenderableContainer);

	virtual void onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent) override;

private:
	StaticRenderableContainer* m_staticRenderableContainer;
};

}