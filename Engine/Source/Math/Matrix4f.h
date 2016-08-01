#pragma once

#include "Common/type.h"

#include <string>

namespace xe
{

class Vector3f;
	
class Matrix4f
{
public:
	float32 m[4][4];

	Matrix4f();

	Matrix4f& initIdentity();
	Matrix4f& initTranslation(const float32 x, const float32 y, const float32 z);
	Matrix4f& initTranslation(const Vector3f& value);
	Matrix4f& initScale(const float32 x, const float32 y, const float32 z);
	Matrix4f& initPerspectiveProjection(const float32 fov,
	                                    const float32 aspectRatio,
	                                    const float32 zNear,
	                                    const float32 zFar);

	// float fov, float aspectRatio, float zNear, float zFar

	Matrix4f mul(const Matrix4f& r);
	Matrix4f& mul(const Matrix4f& var, Matrix4f* result) const;
	Matrix4f& mulLocal(const float32 r);

	Matrix4f& inverse(Matrix4f* result) const;
	float32 determinant() const;

	std::string toStringFormal() const;

	inline void set(const uint32 x, const uint32 y, const float32 value)
	{
		m[x][y] = value;
	}

	inline float32 get(const uint32 x, const uint32 y) const
	{
		return m[x][y];
	}
};// end class Matrix4f

}// end namespace xe