#include "CTestComponent.h"

#include <iostream>

using namespace xe;

CTestComponent::CTestComponent(const CTestComponent& other)
{

}

CTestComponent::CTestComponent(CTestComponent&& other)
{

}

CTestComponent::~CTestComponent()
{

}

void CTestComponent::update(float32 deltaS)
{
	std::cout << "TestComponent updated" << std::endl;
}

CTestComponent& CTestComponent::operator = (CTestComponent left)
{
	std::swap(*this, left);
	return *this;
}