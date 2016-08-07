#include "StaticModelGroupManagerActionListener.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace xe;

StaticModelGroupManagerActionListener::StaticModelGroupManagerActionListener()
{

}

void StaticModelGroupManagerActionListener::onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticModelGroupManagerActionListener: StaticModelGroup added action" << std::endl;
}

void StaticModelGroupManagerActionListener::onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticModelGroupManagerActionListener: StaticModelGroup removal action" << std::endl;
}