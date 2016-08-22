#include "StaticModeGrouplActionListener.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace xe;

typedef StaticModeGrouplActionListener Listener;

Listener::StaticModeGrouplActionListener(StaticRenderableContainer* staticRenderableContainer) :
	m_staticRenderableContainer(staticRenderableContainer)
{
	if(!m_staticRenderableContainer)
	{
		std::cerr << "StaticModeGrouplActionListener Error: m_staticRenderableContainer is null" << std::endl;
	}
}

void Listener::onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent)
{
	std::cout << "StaticModeGrouplActionListener: StaticModelGroup added action" << std::endl;
}

void Listener::onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent)
{
	std::cout << "StaticModeGrouplActionListener: StaticModelGroup removal action" << std::endl;
}
