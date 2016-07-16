#include "Entity.h"
#include "Resource/Component/Component.h"

using namespace xe;

Entity::Entity()
{

}

Entity::~Entity()
{
	for(Component* component : m_components)
	{
		delete component;
	}
}

void Entity::addComponent(std::unique_ptr<Component> component)
{

}