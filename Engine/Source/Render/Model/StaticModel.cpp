#include "StaticModel.h"

using namespace ve;

StaticModel::StaticModel()
{

}

StaticModel::StaticModel(const std::string& fullFilename) :
	m_fullFilename(fullFilename)
{

}

const std::string& StaticModel::getFullFilename() const
{
	return m_fullFilename;
}

const Vector3f& StaticModel::getPosition() const
{
	return m_position;
}

void StaticModel::setPosition(const Vector3f& position)
{
	setPosition(position.x, position.y, position.z);
}

void StaticModel::setPosition(const float32 x, const float32 y, const float32 z)
{
	m_position.set(x, y, z);
}