#include "CameraComponentProcessor.h"
#include "Render/Camera.h"
#include "Render/Component/CCamera.h"
#include "Resource/World/Component/Component.h"
#include "Resource/World/Entity/Entity.h"
#include "Resource/World/Entity/EntityFunctionality.h"

#include <iostream>

using namespace ve;

CameraComponentProcessor::CameraComponentProcessor() : 
	m_camera(nullptr)
{

}

void CameraComponentProcessor::onComponentAdded(CCamera* component, const ComponentIndexType index)
{
	std::cout << "CameraManagerActionListener: Camera added event" << std::endl;

	m_camera->plugCameraComponent(component->getParent()->getComponentHandle<CCamera>());
}

void CameraComponentProcessor::onComponentRemoval(CCamera* component, const ComponentIndexType index)
{
	std::cout << "CameraManagerActionListener: Camera removal event" << std::endl;

	m_camera->unplugCameraComponent();
}