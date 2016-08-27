#pragma once

#include "Common/type.h"
#include "Math/Vector3f.h"
#include "Math/Quaternion.h"

#include <string>

namespace ve
{

class StaticModel
{
public:
	StaticModel();
	StaticModel(const std::string& fullFilename);

	const std::string& getFullFilename() const;

	const Vector3f& getPosition() const;
	void setPosition(const Vector3f& position);
	void setPosition(const float32 x, const float32 y, const float32 z);

	const Quaternion& getOrientation() const;
	void setOrientation(const Vector3f& normalizedAxis, const float32 degree);

private:
	std::string m_fullFilename;

	Vector3f   m_position;
	Quaternion m_orientation;
};

}