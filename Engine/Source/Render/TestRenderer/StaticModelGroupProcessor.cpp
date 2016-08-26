#include "StaticModelGroupProcessor.h"
#include "Resource/Component/Component.h"
#include "Render/Model/AssimpModelParser/AssimpModelParser.h"
#include "Render/Model/StaticModel.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"

#include <iostream>

using namespace ve;

typedef StaticModelGroupProcessor Listener;

Listener::StaticModelGroupProcessor(StaticRenderableContainer* staticRenderableContainer) :
	m_staticRenderableContainer(staticRenderableContainer)
{
	if(!m_staticRenderableContainer)
	{
		std::cerr << "StaticModelGroupProcessor Error: m_staticRenderableContainer is null" << std::endl;
	}

	if(!m_staticModelLoader.init(std::make_shared<AssimpModelParser>()))
	{
		std::cerr << "StaticModelGroupProcessor Error: m_staticModelLoader init failed" << std::endl;
	}
}

void Listener::onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent)
{
	std::cout << "StaticModelGroupProcessor: StaticModelGroup added action" << std::endl;

	StaticModel      staticModel;
	StaticRenderable staticRenderable;

	while(targetComponent->getTypedComponent()->dequeueToLoad(&staticModel))
	{
		if(m_staticModelLoader.load(staticModel, &staticRenderable))
		{
			m_staticRenderableContainer->add(staticRenderable);
		}
		else
		{
			std::cout << "StaticModelGroupProcessor: StaticModel ("
			          << staticModel.getFullFilename()
			          << ") loading failed" << std::endl;
		}
	}
}

void Listener::onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CStaticModelGroup>>& targetComponent)
{
	std::cout << "StaticModelGroupProcessor: StaticModelGroup removal action" << std::endl;
}
