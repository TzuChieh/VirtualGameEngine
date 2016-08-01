#include "CTransform.h"
#include "Core/Engine.h"
#include "Physics/PhysicsEngine.h"

using namespace xe;

CTransform::CTransform()
{

}

CTransform::~CTransform()
{

}

std::shared_ptr<ComponentHandle> CTransform::addToEngine(Engine* engine)
{
	return engine->getPhysicsEngine()->addTransform(*this);
}

ComponentTypeId CTransform::getTypeId()
{
	return Component::getTypeId<CTransform>();
}