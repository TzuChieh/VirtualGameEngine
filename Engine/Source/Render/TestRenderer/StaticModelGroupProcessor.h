#pragma once

#include "Resource/World/Component/TComponentManagerActionListener.h"
#include "Render/Model/StaticModelLoader.h"

namespace ve
{

class CStaticModelGroup;
class StaticRenderableContainer;

class StaticModelGroupProcessor : public TComponentManagerActionListener<CStaticModelGroup>
{
public:
	StaticModelGroupProcessor(StaticRenderableContainer* staticRenderableContainer);

	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent) override;

private:
	StaticRenderableContainer* m_staticRenderableContainer;

	StaticModelLoader m_staticModelLoader;
};

}
