#include "CameraManagerActionListener.h"

#include <iostream>

using namespace xe;

void CameraManagerActionListener::onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "CameraManagerActionListener: Camera added action" << std::endl;
}

void CameraManagerActionListener::onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "CameraManagerActionListener: Camera removal action" << std::endl;
}