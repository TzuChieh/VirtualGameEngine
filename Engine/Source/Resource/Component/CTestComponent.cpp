#include "CTestComponent.h"
#include "Core/Engine.h"
#include "Game/GameProgram.h"

#include <iostream>

using namespace xe;

CTestComponent::CTestComponent()
	: m_message("Hi, I'm CTestComponent with default message"), m_engine(nullptr)
{
	std::cout << "CTestComponent default ctor called" << std::endl;
}

CTestComponent::CTestComponent(const std::string& message)
	: m_message(message), m_engine(nullptr)
{
	std::cout << "CTestComponent set message ctor called" << std::endl;
}

CTestComponent::CTestComponent(const CTestComponent& other)
{
	m_message = other.m_message;
	m_engine = other.m_engine;

	std::cout << "CTestComponent copy ctor called" << std::endl;
}

CTestComponent::CTestComponent(CTestComponent&& other)
{
	m_message = std::move(other.m_message);
	m_engine = other.m_engine;

	std::cout << "CTestComponent move ctor called" << std::endl;
}

CTestComponent::~CTestComponent()
{
	std::cout << "CTestComponent dtor called" << std::endl;
}

std::shared_ptr<ComponentHandle> CTestComponent::addToEngine(Engine* engine)
{
	m_engine = engine;
	return m_engine->getGameProgram()->addTestComponent(*this);
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

std::string CTestComponent::getMessage() const
{
	return m_message;
}

void CTestComponent::setMessage(const std::string& message)
{
	m_message = message;
}