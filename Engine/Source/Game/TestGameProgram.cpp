#include "TestGameProgram.h"
#include "Resource/Component/CTestComponent.h"
#include "Resource/Scene.h"
#include "Resource/Entity/Entity.h"
#include "Resource/Component/TIndexedComponentHandle.h"

#include <iostream>

using namespace xe;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::init(Engine* engine)
{
	// Create a scene.
	m_scene = new Scene();

	// Create an entity from scene.
	Entity testEntity = m_scene->createEntity();

	// You can bind components to an entity to make it behave like something, e.g., tree, enemy, zombie...
	// For now this is only a test component.
	m_scene->bindComponent<CTestComponent>(testEntity, CTestComponent("test test 123"));

	// Flush above information to the engine.
	m_scene->flush(engine);

	// From now on, "testEntity" and its binded components are ready for use!

	// To retrieve a component:
	auto testComponent = testEntity.getComponent<CTestComponent>();
	std::cout << "from getComponent: " << testComponent->getMessage() << std::endl;

	return true;
}

void TestGameProgram::update()
{
	//std::cout << "updated" << std::endl;
}

void TestGameProgram::decompose()
{
	if(m_scene)
	{
		delete m_scene;
	}
}

std::shared_ptr<ComponentHandle> TestGameProgram::addTestComponent(const CTestComponent& testComponent)
{
	uint32 index = m_testComponents.addComponent(testComponent);

	std::cout << "CTestComponent added, index = " << index << std::endl;

	return std::shared_ptr<ComponentHandle>(new TIndexedComponentHandle<CTestComponent>(&m_testComponents, index));
}
