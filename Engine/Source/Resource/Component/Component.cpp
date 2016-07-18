#include "Component.h"

using namespace xe;

ComponentTypeId Component::nextTypeId = 0U;

Component::Component()
: m_componentController(nullptr)
{

}

Component::~Component()
{

}