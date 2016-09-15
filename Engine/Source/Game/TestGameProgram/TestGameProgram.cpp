#include "TestGameProgram.h"
#include "Resource/World/World.h"
#include "Resource/World/Entity/Entity.h"
#include "Render/Component/CCamera.h"
#include "Render/Component/CStaticModelGroup.h"
#include "Physics/Component/CTransform.h"
#include "Resource/World/Component/Component.h"
#include "Core/EngineProxy.h"
#include "Game/Component/CGameLogicGroup.h"
#include "Game/GameLogic/CameraControl.h"
#include "Render/Model/StaticModel.h"
#include "Resource/World/Entity/EntityFunctionality.h"

#include <iostream>
#include <memory>
#include <random>

using namespace ve;

TestGameProgram::~TestGameProgram()
{

}

bool TestGameProgram::initWorld(World* world, const EngineProxy& engineProxy)
{
	// Create an entity from world.
	Entity testEntity(world);

	// You can bind components to an entity to make it behave like tree, enemy, or zombie...
	testEntity->attachComponent(CTestComponent("test test 123"));

	CTransform transform;
	transform.setPosition(0, 0, 10);
	testEntity->attachComponent(transform);

	//CCamera cameraComponent;
	//cameraComponent.setAspectRatio(engineProxy.getDisplayWidthPx(), engineProxy.getDisplayHeightPx());
	//testEntity->attachComponent(cameraComponent);

	//CGameLogicGroup testGameLogicGroup;
	//testGameLogicGroup.addGameLogic("camera control", std::make_shared<CameraControl>());
	//testEntity->attachComponent(testGameLogicGroup);

	CStaticModelGroup staticModelGroup;
	//StaticModel houseModel("./Resource/Model/house.obj");
	//houseModel.setPosition(0, 0, 5);
	//houseModel.setOrientation(Vector3f(0, 1, 0), 30);
	////houseModel.setScale(2.0f);
	//staticModelGroup.queueForLoading("test", houseModel);


	for(std::size_t i = 0; i < 100; i++)
	{
		StaticModel cubeModel("./Resource/Model/cube.obj");

		Vector3f pos(rand() / float32(RAND_MAX), rand() / float32(RAND_MAX), rand() / float32(RAND_MAX));
		pos.mulLocal(50.0f).subLocal(25.0f);
		cubeModel.setPosition(pos);

		Vector3f dir(rand() / float32(RAND_MAX), rand() / float32(RAND_MAX), rand() / float32(RAND_MAX));
		dir.normalizeLocal();
		cubeModel.setOrientation(dir, rand() / float32(RAND_MAX) * 360.0f);

		staticModelGroup.queueForLoading("test", cubeModel);
	}


	testEntity->attachComponent(staticModelGroup);


	// From now on, "testEntity" and its binded components are ready for use!

	// To retrieve a component:
	//auto testComponent1 = testEntity->getComponent<CTestComponent>();
	//std::cout << "from getComponent: " << testComponent1->getMessage() << std::endl;

	// To remove some components:
	testEntity->detachComponent<CTestComponent>();


	// If you try to do
	//
	// testEntity.getComponent<CTestComponent>();
	//
	// here, there will be a warning message, and the program will crash (for now).

	//std::cout << "good component id test: id = " << Component::getTypeId<CTransform>() << std::endl;
	//std::cout << "bad component id test: id = " << Component::getTypeId<TestGameProgram>() << std::endl;
	//std::cout << "bad component id test: id = " << Component::getTypeId<World>() << std::endl;
	
	// Flush above information to the engine.
	world->flushAttachings();
	world->flushDetachings();

	return true;
}

