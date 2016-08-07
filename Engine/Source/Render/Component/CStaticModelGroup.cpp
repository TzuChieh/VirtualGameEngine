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

void CStaticModelGroup::addStaticModel(const std::string& modelName, std::shared_ptr<StaticModel> staticModel)
{

}