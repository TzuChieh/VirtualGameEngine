#include "CStaticMeshGroup.h"
#include "Core/Engine.h"
#include "Render/Renderer.h"

using namespace xe;

CStaticMeshGroup::~CStaticMeshGroup()
{

}

std::shared_ptr<ComponentHandle> CStaticMeshGroup::addToEngine(Engine* engine)
{
	return engine->getRenderer()->addStaticMeshGroup(*this);
}

ComponentTypeId CStaticMeshGroup::getTypeId()
{
	return Component::getTypeId<CStaticMeshGroup>();
}

void CStaticMeshGroup::addStaticMesh(const std::string& meshName, std::shared_ptr<StaticMesh> staticMesh)
{

}