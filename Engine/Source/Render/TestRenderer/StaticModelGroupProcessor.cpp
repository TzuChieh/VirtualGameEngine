#include "StaticModelGroupProcessor.h"
#include "Resource/World/Component/Component.h"
#include "Render/Model/AssimpModelParser/AssimpModelParser.h"
#include "Render/Model/StaticModel.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Render/Renderable/StaticRenderable.h"
#include "Render/Renderable/StaticRenderableContainer.h"

#include <iostream>

using namespace ve;

StaticModelGroupProcessor::StaticModelGroupProcessor() :
	m_staticRenderableContainer(nullptr)
{
	if(!m_staticModelLoader.init(std::make_shared<AssimpModelParser>()))
	{
		std::cerr << "StaticModelGroupProcessor Error: m_staticModelLoader init failed" << std::endl;
	}
}

StaticModelGroupProcessor::~StaticModelGroupProcessor() = default;

void StaticModelGroupProcessor::onComponentAdded(CStaticModelGroup* component, const ComponentIndexType index)
{
	std::cout << "StaticModelGroupProcessor: StaticModelGroup added action" << std::endl;

	StaticModel      staticModel;
	StaticRenderable staticRenderable;

	while(component->dequeueToLoad(&staticModel))
	{
		if(m_staticModelLoader.load(staticModel, &staticRenderable))
		{
			m_staticRenderableContainer->add(staticRenderable);
		}
		else
		{
			std::cout << "StaticModelGroupProcessor: StaticModel <"
			          << staticModel.getFullFilename()
			          << "> loading failed" << std::endl;
		}
	}
}

void StaticModelGroupProcessor::onComponentRemoval(CStaticModelGroup* component, const ComponentIndexType index)
{
	std::cout << "StaticModelGroupProcessor: StaticModelGroup removal event" << std::endl;
}
