#include "GameProgram.h"
#include "Core/Engine.h"
#include "Core/EngineProxy.h"
#include "Resource/World/World.h"
#include "TestComponentActionListener.h"
#include "GameLogicGroupActionListener.h"

using namespace ve;

GameProgram::GameProgram() :
	m_world(nullptr),
	m_engine(nullptr)
{

}

GameProgram::~GameProgram()
{

}

bool GameProgram::init(Engine* engine)
{
	m_engine = engine;
	m_world = engine->getWorld();

	//m_testComponents.addActionListener(std::make_shared<TestComponentActionListener>());
	//m_gameLogicGroups.addActionListener(std::make_shared<GameLogicGroupActionListener>());

	initWorld(m_world, EngineProxy(m_engine));

	return true;
}

void GameProgram::decompose()
{

}

void GameProgram::update(float32 deltaS)
{
	/*const uint32 logicGroupStorageSize = m_gameLogicGroups.storageSize();
	for(uint32 i = 0; i < logicGroupStorageSize; i++)
	{
		if(!m_gameLogicGroups.isIndexValid(i))
		{
			continue;
		}

		m_gameLogicGroups[i].executeGameLogics(deltaS, m_world, EngineProxy(m_engine));
	}*/
}

//std::shared_ptr<ComponentHandle> GameProgram::addTestComponent(const CTestComponent& testComponent)
//{
//	return m_testComponents.addComponent(testComponent);
//}
//
//std::shared_ptr<ComponentHandle> GameProgram::addGameLogicGroup(const CGameLogicGroup& gameLogicGroup)
//{
//	const auto& handle = m_gameLogicGroups.addComponent(gameLogicGroup);
//
//	const uint32 logicGroupStorageSize = m_gameLogicGroups.storageSize();
//	for(uint32 i = 0; i < logicGroupStorageSize; i++)
//	{
//		if(!m_gameLogicGroups.isIndexValid(i))
//		{
//			continue;
//		}
//
//		m_gameLogicGroups[i].initGameLogics();
//	}
//
//	return handle;
//}