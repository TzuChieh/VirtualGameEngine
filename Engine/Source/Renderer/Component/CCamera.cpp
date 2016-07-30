#include "CCamera.h"
#include "Core/Engine.h"
#include "Renderer/Renderer.h"

#include <iostream>

using namespace xe;

CCamera::~CCamera()
{

}

std::shared_ptr<ComponentHandle> CCamera::addToEngine(Engine* engine)
{
	return engine->getRenderer()->addCamera(*this);
}

ComponentTypeId CCamera::getTypeId()
{
	std::cout << "CCamera type ID: " << Component::getTypeId<CCamera>() << std::endl;
	return Component::getTypeId<CCamera>();
}