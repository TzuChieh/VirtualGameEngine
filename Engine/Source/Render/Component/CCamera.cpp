#include "CCamera.h"
#include "Core/Engine.h"
#include "Render/Renderer.h"

#include <iostream>
#include <cmath>

using namespace ve;

CCamera::CCamera()
	: m_fov(75.0f / 180.0f * 3.14159265f), m_zNear(0.1f), m_zFar(10000.0f), m_aspectRatio(1.0f)
{

}

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