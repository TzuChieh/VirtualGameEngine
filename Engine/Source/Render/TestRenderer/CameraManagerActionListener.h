#pragma once

#include "Resource/World/Component/TComponentManagerActionListener.h"

namespace ve
{

class CCamera;
class Camera;

class CameraManagerActionListener : public TComponentManagerActionListener<CCamera>
{
public:
	CameraManagerActionListener(Camera* camera);

	virtual void onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CCamera>>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CCamera>>& targetComponent) override;

private:
	Camera* m_camera;
};

}