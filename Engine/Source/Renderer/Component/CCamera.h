#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
#include "Resource/Component/ComponentHandle.h"

namespace xe
{

class CCamera : public Component
{
public:
	CCamera();
	virtual ~CCamera() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	inline float32 getFov() const
	{
		return m_fov;
	}

	inline float32 getZnear() const
	{
		return m_zNear;
	}

	inline float32 getZfar() const
	{
		return m_zFar;
	}

	inline float32 getAspectRatio() const
	{
		return m_aspectRatio;
	}

	inline void setFovDeg(float32 fovDeg)
	{
		m_fov = fovDeg / 180.0f * 3.14159265f;
	}

	inline void setAspectRatio(float32 aspectRatio)
	{
		m_aspectRatio = aspectRatio;
	}

	inline void setAspectRatio(uint32 width, uint32 height)
	{
		setAspectRatio(static_cast<float32>(width) / static_cast<float32>(height));
	}

private:
	float32 m_fov;
	float32 m_zNear;
	float32 m_zFar;
	float32 m_aspectRatio;
};

}