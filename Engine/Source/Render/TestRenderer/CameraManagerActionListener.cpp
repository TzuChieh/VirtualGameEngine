#include "CameraManagerActionListener.h"
#include "Resource/Component/TTypedComponentHandle.h"
#include "Render/Camera.h"
#include "Render/Component/CCamera.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace ve;

CameraManagerActionListener::CameraManagerActionListener(Camera* camera)
	: m_camera(camera)
{

}

void CameraManagerActionListener::onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CCamera>>& targetComponent)
{
	std::cout << "CameraManagerActionListener: Camera added action" << std::endl;

	m_camera->plugCameraComponent(targetComponent);
}

void CameraManagerActionListener::onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CCamera>>& targetComponent)
{
	std::cout << "CameraManagerActionListener: Camera removal action" << std::endl;

	m_camera->unplugCameraComponent();
}