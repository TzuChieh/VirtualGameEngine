#pragma once

#include "Resource/World/Component/TComponentHandle.h"
#include "Render/Component/CCamera.h"
#include "Math/Matrix4f.h"

#include <memory>

namespace ve
{

class Camera
{
public:
	Camera();

	void update();

	void plugCameraComponent(const TComponentHandle<CCamera>& cameraComponentHandle);
	void unplugCameraComponent();

	inline const Matrix4f& getViewMatrix() const
	{
		return m_viewMatrix;
	}

	inline const Matrix4f& getProjectionMatrix() const
	{
		return m_projectionMatrix;
	}

	inline const Matrix4f& getViewProjectionMatrix() const
	{
		return m_viewProjectionMatrix;
	}

private:
	TComponentHandle<CCamera> m_cameraComponentHandle;

	Matrix4f m_viewMatrix;
	Matrix4f m_projectionMatrix;
	Matrix4f m_viewProjectionMatrix;
};

}