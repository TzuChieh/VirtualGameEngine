#pragma once

#include "Resource/Component/TTypedComponentHandle.h"
#include "Render/Component/CCamera.h"
#include "Math/Matrix4f.h"

#include <memory>

namespace xe
{

class Camera
{
public:
	Camera();

	void update();

	void plugCameraComponent(const TTypedComponentHandle<CCamera>& cameraData);
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
	TTypedComponentHandle<CCamera> m_cameraData;

	Matrix4f m_viewMatrix;
	Matrix4f m_projectionMatrix;
	Matrix4f m_viewProjectionMatrix;
};

}