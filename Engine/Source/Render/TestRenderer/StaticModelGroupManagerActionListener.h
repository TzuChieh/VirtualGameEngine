#pragma once

#include "Resource/Component/TComponentManagerActionListener.h"

namespace xe
{

class CStaticModelGroup;
class StaticRenderableContainer;

class StaticModelGroupManagerActionListener : public TComponentManagerActionListener<CStaticModelGroup>
{
public:
	StaticModelGroupManagerActionListener(StaticRenderableContainer* staticRenderableContainer);

	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent) override;

private:
	StaticRenderableContainer* m_staticRenderableContainer;
};

}