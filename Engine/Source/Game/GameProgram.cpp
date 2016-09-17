#include "GameProgram.h"
#include "Core/Engine.h"
#include "Core/EngineProxy.h"
#include "Resource/World/World.h"

using namespace ve;

GameProgram::GameProgram() :
	m_engine(nullptr)
{

}

GameProgram::~GameProgram()
{

}

bool GameProgram::init(Engine* engine)
{
	m_engine = engine;
	
	m_engine->getWorld()->addComponentListener(&m_testComponentProcessor);
	m_engine->getWorld()->addComponentListener(&m_gameLogicGroupProcessor);

	initWorld(engine->getWorld(), EngineProxy(m_engine));

	return true;
}

void GameProgram::decompose()
{
	m_engine->getWorld()->removeComponentListener(&m_testComponentProcessor);
}

void GameProgram::update(float32 deltaS)
{
	auto* database = m_engine->getWorld()->getEntityComponentDatabase(); 
	TComponentStorage<CGameLogicGroup>* gameLogicGroups = database->getComponentStorage<CGameLogicGroup>();

	for(auto& gameLogicGroup : *gameLogicGroups)
	{
		gameLogicGroup.executeGameLogics(deltaS, m_engine->getWorld(), EngineProxy(m_engine));
	}
}