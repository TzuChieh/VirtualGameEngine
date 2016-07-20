#include "TestGameProgram.h"
#include "Resource/Component/TContinuousMemoryComponentManager.h"
#include "Resource/Component/CTestComponent.h"
#include "Resource/Scene.h"
#include "Resource/Entity/Entity.h"
#include "Resource/Component/ComponentHandle.h"

#include <iostream>

using namespace xe;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::init(Engine* engine)
{
	m_scene = new Scene(0);

	Entity testEntity = m_scene->createEntity();
	testEntity.removeFromScene();
	testEntity.removeFromScene();
	m_scene->removeEntity(testEntity);

	m_scene->flush(engine);

	ComponentHandle testHandle;
	testHandle.getComponent<Entity>();
	testHandle.getComponent<Component>();

	//addTestComponent(CTestComponent());

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

void TestGameProgram::addTestComponent(CTestComponent&& testComponent)
{
	m_testComponentManager.addComponent(std::move(testComponent));
}
