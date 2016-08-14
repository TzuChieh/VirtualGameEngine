#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
#include "Resource/Component/ComponentHandle.h"
#include "Math/Vector3f.h"
#include "Math/Quaternion.h"

#include <memory>

namespace xe
{

class Engine;

class CTransform : public Component
{
public:
	CTransform();
	virtual ~CTransform() override;

	virtual std::shared_ptr<ComponentHandle> addToEngine(Engine* engine) override;
	virtual ComponentTypeId getTypeId() override;

	void rotateDeg(const Vector3f& unitAxis, const float32 degree);

	Vector3f getForwardUnitDirection() const;
	void getForwardUnitDirection(Vector3f* out_result) const;

	Vector3f getRightUnitDirection() const;
	void getRightUnitDirection(Vector3f* out_result) const;

	Vector3f getUpUnitDirection() const;
	void getUpUnitDirection(Vector3f* out_result) const;

	inline const Vector3f& getPosition() const
	{
		return m_position;
	}

	inline const Vector3f& getScale() const
	{
		return m_scale;
	}

	inline const Quaternion& getRotation() const
	{
		return m_rotation;
	}

	inline void setPosition(float32 x, float32 y, float32 z)
	{
		m_position.set(x, y, z);
	}

	inline void setPosition(const Vector3f& position)
	{
		m_position.set(position);
	}

	inline void setScale(float32 x, float32 y, float32 z)
	{
		m_scale.set(x, y, z);
	}

	inline void setScale(float32 uniformScaleFactor)
	{
		m_scale.set(uniformScaleFactor);
	}

	inline void setRotation(const Quaternion& rot)
	{
		m_rotation.set(rot);
	}

	inline void setRotation(const Vector3f& normalizedAxis, const float32 angle)
	{
		m_rotation.setRot(normalizedAxis, angle);
	}

private:
	Vector3f   m_position;
	Vector3f   m_scale;
	Quaternion m_rotation;
};

}