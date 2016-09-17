#include "CTransform.h"
#include "Core/Engine.h"
#include "Physics/PhysicsEngine.h"

using namespace ve;

CTransform::CTransform() :
	m_position(0, 0, 0),
	m_rotation(0, 0, 0, 1),
	m_scale(1, 1, 1)
{

}

CTransform::~CTransform()
{

}

ComponentTypeId CTransform::getTypeId()
{
	return Component::getTypeId<CTransform>();
}

void CTransform::rotateDeg(const Vector3f& unitAxis, const float32 degree)
{
	m_rotation = Quaternion(unitAxis, degree / 180.0f * 3.14159265f).mulLocal(m_rotation).normalizeLocal();
}

Vector3f CTransform::getForwardUnitDirection() const
{
	return Vector3f::UNIT_NEGATIVE_Z_AXIS.rotate(m_rotation);
}

void CTransform::getForwardUnitDirection(Vector3f* out_result) const
{
	Vector3f::UNIT_NEGATIVE_Z_AXIS.rotate(m_rotation, out_result);
}

Vector3f CTransform::getRightUnitDirection() const
{
	return Vector3f::UNIT_X_AXIS.rotate(m_rotation);
}

void CTransform::getRightUnitDirection(Vector3f* out_result) const
{
	Vector3f::UNIT_X_AXIS.rotate(m_rotation, out_result);
}

Vector3f CTransform::getUpUnitDirection() const
{
	return Vector3f::UNIT_Y_AXIS.rotate(m_rotation);
}

void CTransform::getUpUnitDirection(Vector3f* out_result) const
{
	Vector3f::UNIT_Y_AXIS.rotate(m_rotation, out_result);
}