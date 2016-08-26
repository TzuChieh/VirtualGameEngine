#include "TransformManagerActionListener.h"

#include <iostream>

using namespace ve;

TransformManagerActionListener::TransformManagerActionListener()
{

}

void TransformManagerActionListener::onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CTransform>>& targetComponent)
{
	std::cout << "TransformManagerActionListener: transform component added event" << std::endl;
}

void TransformManagerActionListener::onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CTransform>>& targetComponent)
{
	std::cout << "TransformManagerActionListener: transform component removal event" << std::endl;
}