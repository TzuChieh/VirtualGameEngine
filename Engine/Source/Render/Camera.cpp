#include "Camera.h"
#include "Render/Component/CCamera.h"
#include "Physics/Component/CTransform.h"

#include <iostream>

using namespace xe;

Camera::Camera()
{
	m_viewMatrix.initIdentity();
	m_projectionMatrix.initIdentity();
	m_viewProjectionMatrix.initIdentity();
}

void Camera::update()
{
	// TODO: check if data changed

	if(m_cameraData.isValid())
	{
		m_projectionMatrix.initPerspectiveProjection(m_cameraData->getFov(),
		                                             m_cameraData->getAspectRatio(),
		                                             m_cameraData->getZnear(),
		                                             m_cameraData->getZfar());

		CTransform* transform = m_cameraData->getParent().getComponent<CTransform>();
		if(transform)
		{
			std::cout << "has transform" << std::endl;
		}
		else
		{
			std::cout << "no transform" << std::endl;
		}
	}
}

void Camera::plugCameraComponent(const TTypedComponentHandle<CCamera>& cameraData)
{
	if(!cameraData.isValid())
	{
		std::cerr << "Camera Warning: underlying component data is empty" << std::endl;
	}

	m_cameraData = cameraData;
}

void Camera::unplugCameraComponent()
{
	m_cameraData.release();
}