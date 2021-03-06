#include "Camera.h"
#include "Render/Component/CCamera.h"
#include "Physics/Component/CTransform.h"
#include "Resource/World/Entity/Entity.h"
#include "Resource/World/Entity/EntityFunctionality.h"

#include <iostream>

using namespace ve;

Camera::Camera()
{
	m_viewMatrix.initIdentity();
	m_projectionMatrix.initIdentity();
	m_viewProjectionMatrix.initIdentity();
}

void Camera::update()
{
	// TODO: check if data changed

	if(m_cameraComponentHandle.isValid())
	{
		const auto& cameraComponent = m_cameraComponentHandle.getComponent();
		m_projectionMatrix.initPerspectiveProjection(cameraComponent->getFov(),
		                                             cameraComponent->getAspectRatio(),
		                                             cameraComponent->getZnear(),
		                                             cameraComponent->getZfar());

		CTransform* transform = cameraComponent->getParent()->getComponent<CTransform>();
		if(transform)
		{
			Matrix4f cameraTranslationMat;
			Matrix4f cameraRotationMat;
			cameraTranslationMat.initTranslation(transform->getPosition().mul(-1.0f));
			cameraRotationMat.initRotation(transform->getRotation().conjugate());

			cameraRotationMat.mul(cameraTranslationMat, &m_viewMatrix);

			//std::cout << cameraRotationMat.toStringFormal() << std::endl;
		}
		else
		{
			std::cout << "no transform" << std::endl;
		}

		m_projectionMatrix.mul(m_viewMatrix, &m_viewProjectionMatrix);
	}
	else
	{
		std::cout << "no camera data" << std::endl;
	}
}

void Camera::plugCameraComponent(const TComponentHandle<CCamera>& cameraComponentHandle)
{
	if(!cameraComponentHandle.isValid())
	{
		std::cerr << "Camera Warning: underlying component handle is invalid" << std::endl;
	}

	m_cameraComponentHandle = cameraComponentHandle;
}

void Camera::unplugCameraComponent()
{
	m_cameraComponentHandle.makeInvalid();
}

//void Camera::plugCameraComponent(const std::shared_ptr<TTypedComponentHandle<CCamera>>& cameraData)
//{
//	if(!cameraData->isValid())
//	{
//		std::cerr << "Camera Warning: underlying component data is empty" << std::endl;
//	}
//
//	m_cameraData = cameraData;
//}
//
//void Camera::unplugCameraComponent()
//{
//	m_cameraData->relinquish();
//}