#include "CStaticModelGroup.h"
#include "Core/Engine.h"
#include "Render/Renderer.h"

using namespace xe;

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

bool CStaticModelGroup::dequeueToLoad(const StaticModelLoader& staticModelLoader)
{
	return true;
}