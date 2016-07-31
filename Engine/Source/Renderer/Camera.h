#pragma once

#include "Resource/Component/TTypedComponentHandle.h"
#include "Renderer/Component/CCamera.h"
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

private:
	TTypedComponentHandle<CCamera> m_cameraData;

	Matrix4f m_projectionMatrix;
};

}