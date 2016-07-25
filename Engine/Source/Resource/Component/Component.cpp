#include "Component.h"

using namespace xe;

ComponentTypeId Component::nextTypeId = 0U;

Component::Component()
{

}

Component::~Component()
{

}

Entity Component::getParent()
{
	return m_parent;
}

void Component::setParent(const Entity& parent)
{
	m_parent = parent;
}