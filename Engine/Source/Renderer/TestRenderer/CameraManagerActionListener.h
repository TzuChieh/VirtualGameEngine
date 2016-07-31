#pragma once

#include "Resource/Component/ComponentManagerActionListener.h"

namespace xe
{

class Camera;

class CameraManagerActionListener : public ComponentManagerActionListener
{
public:
	CameraManagerActionListener(Camera* camera);

	virtual void onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent) override;
	virtual void onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent) override;

private:
	Camera* m_camera;
};

}