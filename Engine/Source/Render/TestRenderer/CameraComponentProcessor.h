#pragma once

#include "Resource/World/Event/TComponentListener.h"

namespace ve
{

class CCamera;
class Camera;

class CameraComponentProcessor : public TComponentListener<CCamera>
{
public:
	CameraComponentProcessor();

	virtual void onComponentAdded(CCamera* component, const ComponentIndexType index) override;
	virtual void onComponentRemoval(CCamera* component, const ComponentIndexType index) override;

	// FIXME: temp hack only
	inline void setCamera(Camera* camera)
	{
		m_camera = camera;
	}

private:
	Camera* m_camera;
};

}