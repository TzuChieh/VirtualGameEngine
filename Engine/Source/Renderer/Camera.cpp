#include "Camera.h"
#include "Renderer/Component/CCamera.h"

#include <iostream>

using namespace xe;

Camera::Camera()
{
	m_projectionMatrix.initIdentity();
}

void Camera::update()
{
	if(!m_cameraData.isValid())
	{
		std::cerr << "Camera Warning: underlying component data is empty" << std::endl;
		return;
	}

	// TODO: check if data changed

	m_projectionMatrix.initPerspectiveProjection(m_cameraData->getFov(),
												 m_cameraData->getAspectRatio(),
												 m_cameraData->getZnear(),
												 m_cameraData->getZfar());
}

void Camera::plugCameraComponent(const TTypedComponentHandle<CCamera>& cameraData)
{
	m_cameraData = cameraData;
}

void Camera::unplugCameraComponent()
{
	m_cameraData.release();
}