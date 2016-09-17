#include "TransformComponentProcessor.h"

#include <iostream>

using namespace ve;

TransformComponentProcessor::TransformComponentProcessor()
{

}

TransformComponentProcessor::~TransformComponentProcessor()
{

}

void TransformComponentProcessor::onComponentAdded(CTransform* component, const ComponentIndexType index)
{
	std::cout << "TransformComponentProcessor: transform component added event" << std::endl;
}
void TransformComponentProcessor::onComponentRemoval(CTransform* component, const ComponentIndexType index)
{
	std::cout << "TransformComponentProcessor: transform component removal event" << std::endl;
}