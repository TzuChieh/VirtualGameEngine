#include "Quaternion.h"
#include "Vector3f.h"
#include "Matrix4f.h"

using namespace xe;

Quaternion::Quaternion(const Vector3f& normalizedAxis, const float32 angle)
{
	setRot(normalizedAxis, angle);
}

void Quaternion::setRot(const Vector3f& normalizedAxis, const float32 angle)
{
	float32 sinHalfAngle = sin(angle / 2.0f);
	float32 cosHalfAngle = cos(angle / 2.0f);

	x = normalizedAxis.x * sinHalfAngle;
	y = normalizedAxis.y * sinHalfAngle;
	z = normalizedAxis.z * sinHalfAngle;
	w = cosHalfAngle;
}

void Quaternion::toRotationMatrix(Matrix4f* result) const
{
	result->m[0][0] = 1.0f - 2.0f*(y*y + z*z);
	result->m[0][1] = 2.0f*(x*y - z*w);
	result->m[0][2] = 2.0f*(y*w + x*z);
	result->m[0][3] = 0.0f;

	result->m[1][0] = 2.0f*(x*y + z*w);
	result->m[1][1] = 1.0f - 2.0f*(x*x + z*z);
	result->m[1][2] = 2.0f*(y*z - x*w);
	result->m[1][3] = 0.0f;

	result->m[2][0] = 2.0f*(x*z - y*w);
	result->m[2][1] = 2.0f*(y*z + x*w);
	result->m[2][2] = 1.0f - 2.0f*(x*x + y*y);
	result->m[2][3] = 0.0f;

	result->m[3][0] = 0.0f;
	result->m[3][1] = 0.0f;
	result->m[3][2] = 0.0f;
	result->m[3][3] = 1.0f;
}