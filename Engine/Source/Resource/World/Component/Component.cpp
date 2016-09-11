#include "Component.h"

#include <iostream>

DEFINE_LOG_SENDER(Component);

namespace ve
{

ComponentTypeId Component::nextTypeId = 0U;

Component::Component() : 
	m_parent(nullptr)
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

}// end namespace ve