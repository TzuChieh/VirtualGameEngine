#include "StaticMeshGroupManagerActionListener.h"
#include "Resource/Component/Component.h"

#include <iostream>

using namespace xe;

StaticMeshGroupManagerActionListener::StaticMeshGroupManagerActionListener()
{

}

void StaticMeshGroupManagerActionListener::onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticMeshGroupManagerActionListener: StaticMeshGroup added action" << std::endl;
}

void StaticMeshGroupManagerActionListener::onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "StaticMeshGroupManagerActionListener: StaticMeshGroup removal action" << std::endl;
}