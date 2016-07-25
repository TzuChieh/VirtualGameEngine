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
	m_scene = new Scene();

	Entity testEntity = m_scene->createEntity();
	m_scene->bindComponent<CTestComponent>(testEntity, CTestComponent());
	//testEntity.removeFromScene();
	//testEntity.removeFromScene();
	//m_scene->removeEntity(testEntity);

	m_scene->flush(engine);

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
