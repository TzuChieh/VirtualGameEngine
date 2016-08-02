#pragma once

#include "Common/type.h"
#include "Resource/Component/Component.h"
#include "Resource/Component/ComponentHandle.h"
#include "Math/Vector3f.h"

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

	inline const Vector3f& getPosition() const
	{
		return m_position;
	}

	inline const Vector3f& getScale() const
	{
		return m_scale;
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

private:
	Vector3f m_position;
	Vector3f m_scale;
};

}