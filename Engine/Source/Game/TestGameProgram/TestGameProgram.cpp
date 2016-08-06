#include "TestGameProgram.h"
#include "Resource/Scene.h"
#include "Resource/Entity/Entity.h"
#include "TestComponentActionListener.h"
#include "GameLogicGroupActionListener.h"
#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticMeshGroup.h"
#include "Physics/Component/CTransform.h"
#include "Core/Engine.h"
#include "Core/Platform.h"
#include "Resource/Component/Component.h"

#include "Game/Component/CGameLogicGroup.h"
#include "Game/GameLogic/CameraControl.h"

#include <iostream>
#include <memory>

using namespace xe;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::init(Engine* engine)
{
	m_engine = engine;

	m_testComponents.addActionListener(std::make_shared<TestComponentActionListener>());
	m_gameLogicGroups.addActionListener(std::make_shared<GameLogicGroupActionListener>());

	initScene(engine);

	return true;
}

void TestGameProgram::initScene(Engine* engine)
{
	// Create a scene.
	m_scene = new Scene(engine);

	// Create an entity from scene.
	Entity testEntity = m_scene->createEntity();

	// You can bind components to an entity to make it behave like tree, enemy, or zombie...
	m_scene->bindComponent<CTestComponent>(testEntity, CTestComponent("test test 123"));

	CTransform transform;
	transform.setPosition(0, 0, 10);
	m_scene->bindComponent<CTransform>(testEntity, transform);

	CCamera cameraComponent;
	cameraComponent.setAspectRatio(engine->getPlatform()->getWidthPx(), engine->getPlatform()->getHeightPx());
	m_scene->bindComponent<CCamera>(testEntity, cameraComponent);

	CGameLogicGroup testGameLogicGroup;
	testGameLogicGroup.addGameLogic("camera control", std::make_shared<CameraControl>());
	m_scene->bindComponent<CGameLogicGroup>(testEntity, testGameLogicGroup);

	CStaticMeshGroup staticMeshGroup;
	m_scene->bindComponent<CStaticMeshGroup>(testEntity, staticMeshGroup);

	// Flush above information to the engine.
	m_scene->flush();

	// From now on, "testEntity" and its binded components are ready for use!

	// To retrieve a component:
	auto testComponent1 = testEntity.getComponent<CTestComponent>();
	std::cout << "from getComponent: " << testComponent1->getMessage() << std::endl;

	// To remove some components:
	testEntity.removeComponent<CTestComponent>();


	// If you try to do
	//
	// testEntity.getComponent<CTestComponent>();
	//
	// here, there will be a warning message, and the program will crash (for now).

	std::cout << "good component id test: id = " << Component::getTypeId<CTransform>() << std::endl;
	std::cout << "bad component id test: id = " << Component::getTypeId<TestGameProgram>() << std::endl;

	// temp
	const uint32 logicGroupStorageSize = m_gameLogicGroups.storageSize();
	for(uint32 i = 0; i < logicGroupStorageSize; i++)
	{
		if(!m_gameLogicGroups.isIndexValid(i))
		{
			continue;
		}

		m_gameLogicGroups[i].initGameLogics();
	}
}

void TestGameProgram::update(float32 deltaS)
{
	const uint32 logicGroupStorageSize = m_gameLogicGroups.storageSize();
	for(uint32 i = 0; i < logicGroupStorageSize; i++)
	{
		if(!m_gameLogicGroups.isIndexValid(i))
		{
			continue;
		}

		m_gameLogicGroups[i].executeGameLogics(deltaS, m_engine);
	}
}

void TestGameProgram::decompose()
{
	delete m_scene;
}

std::shared_ptr<ComponentHandle> TestGameProgram::addTestComponent(const CTestComponent& testComponent)
{
	return m_testComponents.addComponent(testComponent);
}

std::shared_ptr<ComponentHandle> TestGameProgram::addGameLogicGroup(const CGameLogicGroup& gameLogicGroup)
{
	return m_gameLogicGroups.addComponent(gameLogicGroup);
}
