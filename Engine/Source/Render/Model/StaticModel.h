#pragma once

#include "Common/type.h"
#include "Math/Vector3f.h"

#include <string>

namespace xe
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

private:
	std::string m_fullFilename;

	Vector3f m_position;
};

}