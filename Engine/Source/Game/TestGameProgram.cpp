#include "TestGameProgram.h"
#include "Resource/Component/TContinuousMemoryComponentManager.h"
#include "Resource/Component/CTestComponent.h"

#include <iostream>

using namespace xe;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::init(Engine* engine)
{
	/*TContinuousMemoryComponentManager<CTestComponent> test;
	test.addComponent(CTestComponent());
	test.updateComponents(0.0f);*/

	addTestComponent(CTestComponent());

	return true;
}

void TestGameProgram::update()
{
	//std::cout << "updated" << std::endl;
}

void TestGameProgram::decompose()
{

}

void TestGameProgram::addTestComponent(CTestComponent&& testComponent)
{
	m_testComponentManager.addComponent(std::move(testComponent));
}
