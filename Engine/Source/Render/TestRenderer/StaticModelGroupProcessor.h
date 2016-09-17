#pragma once

#include "Resource/World/Event/TComponentListener.h"
#include "Render/Model/StaticModelLoader.h"

namespace ve
{

class CStaticModelGroup;
class StaticRenderableContainer;

class StaticModelGroupProcessor : public TComponentListener<CStaticModelGroup>
{
public:
	StaticModelGroupProcessor();
	virtual ~StaticModelGroupProcessor() override;

	virtual void onComponentAdded(CStaticModelGroup* component, const ComponentIndexType index) override;
	virtual void onComponentRemoval(CStaticModelGroup* component, const ComponentIndexType index) override;

	inline void setStaticRenderableContainer(StaticRenderableContainer* staticRenderableContainer)
	{
		m_staticRenderableContainer = staticRenderableContainer;
	}

private:
	StaticRenderableContainer* m_staticRenderableContainer;

	StaticModelLoader m_staticModelLoader;
};

}
