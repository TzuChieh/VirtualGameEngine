#include "TestComponentActionListener.h"

#include <iostream>

using namespace ve;

void TestComponentActionListener::onComponentAdded(const std::shared_ptr<TTypedComponentHandle<CTestComponent>>& targetComponent)
{
	std::cout << "TestComponentActionListener: TestComponent added action" << std::endl;
}

void TestComponentActionListener::onComponentRemoval(const std::shared_ptr<TTypedComponentHandle<CTestComponent>>& targetComponent)
{
	std::cout << "TestComponentActionListener: TestComponent removal action" << std::endl;
}