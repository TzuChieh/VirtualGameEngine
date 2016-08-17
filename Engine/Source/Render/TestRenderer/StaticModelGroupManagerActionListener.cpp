#include "StaticModelGroupManagerActionListener.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace xe;

typedef StaticModelGroupManagerActionListener Listener;

Listener::StaticModelGroupManagerActionListener(StaticRenderableContainer* staticRenderableContainer) : 
	m_staticRenderableContainer(staticRenderableContainer)
{
	if(!m_staticRenderableContainer)
	{
		std::cerr << "StaticModelGroupManagerActionListener Error: m_staticRenderableContainer is null" << std::endl;
	}
}

void Listener::onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticModelGroupManagerActionListener: StaticModelGroup added action" << std::endl;
}

void Listener::onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticModelGroupManagerActionListener: StaticModelGroup removal action" << std::endl;
}
