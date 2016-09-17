#include "TestComponentProcessor.h"

#include <iostream>

using namespace ve;

TestComponentProcessor::~TestComponentProcessor() = default;

void TestComponentProcessor::onComponentAdded(CTestComponent* component, const ComponentIndexType index)
{
	std::cout << "TestComponentProcessor: TestComponent added event" << std::endl;
}

void TestComponentProcessor::onComponentRemoval(CTestComponent* component, const ComponentIndexType index)
{
	std::cout << "TestComponentProcessor: TestComponent removal event" << std::endl;
}