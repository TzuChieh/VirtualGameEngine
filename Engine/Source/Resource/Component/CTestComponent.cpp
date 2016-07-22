#include "CTestComponent.h"

#include <iostream>

using namespace xe;

CTestComponent::CTestComponent()
{
	std::cout << "CTestComponent default ctor called" << std::endl;
}

CTestComponent::CTestComponent(const CTestComponent& other)
{
	std::cout << "CTestComponent copy ctor called" << std::endl;
}

CTestComponent::CTestComponent(CTestComponent&& other)
{
	std::cout << "CTestComponent move ctor called" << std::endl;
}

CTestComponent::~CTestComponent()
{
	std::cout << "CTestComponent dtor called" << std::endl;
}

void CTestComponent::addToEngine(Engine* engine)
{

}

//CTestComponent& CTestComponent::operator = (CTestComponent left)
//{
//	std::swap(*this, left);
//	return *this;
//}