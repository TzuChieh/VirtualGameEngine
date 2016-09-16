#include "CameraComponentProcessor.h"
#include "Render/Camera.h"
#include "Render/Component/CCamera.h"
#include "Resource/World/Component/Component.h"

#include <iostream>

using namespace ve;

CameraComponentProcessor::CameraComponentProcessor() : 
	m_camera(nullptr)
{

}

void CameraComponentProcessor::onComponentAdded(CCamera* component, const ComponentIndexType index)
{
	std::cout << "CameraManagerActionListener: Camera added action" << std::endl;

	//m_camera->plugCameraComponent(targetComponent);
}

void CameraComponentProcessor::onComponentRemoval(CCamera* component, const ComponentIndexType index)
{
	std::cout << "CameraManagerActionListener: Camera removal action" << std::endl;

	//m_camera->unplugCameraComponent();
}