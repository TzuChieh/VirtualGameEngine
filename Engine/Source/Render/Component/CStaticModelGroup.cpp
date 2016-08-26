#include "CStaticModelGroup.h"
#include "Core/Engine.h"
#include "Render/Renderer.h"

using namespace ve;

CStaticModelGroup::~CStaticModelGroup()
{

}

std::shared_ptr<ComponentHandle> CStaticModelGroup::addToEngine(Engine* engine)
{
	return engine->getRenderer()->addStaticModelGroup(*this);
}

ComponentTypeId CStaticModelGroup::getTypeId()
{
	return Component::getTypeId<CStaticModelGroup>();
}

void CStaticModelGroup::queueForLoading(const std::string& modelName, const StaticModel& staticModel)
{
	m_queueForLoadingStaticModels.push(staticModel);
}

bool CStaticModelGroup::dequeueToLoad(StaticModel* out_staticModel)
{
	if(m_queueForLoadingStaticModels.empty())
	{
		return false;
	}

	*out_staticModel = m_queueForLoadingStaticModels.front();
	m_queueForLoadingStaticModels.pop();

	return true;
}