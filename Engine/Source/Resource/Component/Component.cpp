#include "Component.h"
#include "ComponentHandle.h"

using namespace xe;

ComponentTypeId Component::nextTypeId = 0U;

Component::Component()
: m_componentHandle(new ComponentHandle(this))
{

}

Component::~Component()
{
	delete m_componentHandle;
}