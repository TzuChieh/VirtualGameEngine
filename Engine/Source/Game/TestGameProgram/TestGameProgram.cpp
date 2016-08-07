#include "TestGameProgram.h"
#include "Resource/Scene.h"
#include "Resource/Entity/Entity.h"
#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Physics/Component/CTransform.h"
#include "Resource/Component/Component.h"
#include "Core/EngineProxy.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Game/GameLogic/CameraControl.h"

#include <iostream>
#include <memory>

using namespace xe;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::initScene(Scene* scene, const EngineProxy& engineProxy)
{
	// Create an entity from scene.
	Entity testEntity = scene->createEntity();

	// You can bind components to an entity to make it behave like tree, enemy, or zombie...
	scene->bindComponent<CTestComponent>(testEntity, CTestComponent("test test 123"));

	CTransform transform;
	transform.setPosition(0, 0, 10);
	scene->bindComponent<CTransform>(testEntity, transform);

	CCamera cameraComponent;
	cameraComponent.setAspectRatio(engineProxy.getDisplayWidthPx(), engineProxy.getDisplayHeightPx());
	scene->bindComponent<CCamera>(testEntity, cameraComponent);

	CGameLogicGroup testGameLogicGroup;
	testGameLogicGroup.addGameLogic("camera control", std::make_shared<CameraControl>());
	scene->bindComponent<CGameLogicGroup>(testEntity, testGameLogicGroup);

	CStaticModelGroup staticModelGroup;
	scene->bindComponent<CStaticModelGroup>(testEntity, staticModelGroup);

	// Flush above information to the engine.
	scene->flush();

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

	return true;
}

