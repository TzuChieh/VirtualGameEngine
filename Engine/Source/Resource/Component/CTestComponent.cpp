#include "CTestComponent.h"
#include "Core/Engine.h"
#include "Game/GameProgram.h"

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

std::shared_ptr<ComponentHandle> CTestComponent::addToEngine(Engine* engine)
{
	return engine->getGameProgram()->addTestComponent(*this);
}

ComponentTypeId CTestComponent::getTypeId()
{
	return Component::getTypeId<CTestComponent>();
}

//CTestComponent& CTestComponent::operator = (CTestComponent left)
//{
//	std::swap(*this, left);
//	return *this;
//}