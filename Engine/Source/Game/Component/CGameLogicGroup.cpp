#include "CGameLogicGroup.h"
#include "Game/GameLogic/GameLogic.h"
#include "Core/Engine.h"
#include "Game/GameProgram.h"

using namespace ve;

CGameLogicGroup::~CGameLogicGroup()
{

}

void CGameLogicGroup::initGameLogics()
{
	for(auto& keyValuePair : m_gameLogicsNameMap)
	{
		keyValuePair.second->setParentEntity(getParent());
	}
}

void CGameLogicGroup::executeGameLogics(float32 deltaS, World* world, const EngineProxy& engineProxy)
{
	for(auto& keyValuePair : m_gameLogicsNameMap)
	{
		keyValuePair.second->execute(deltaS, world, engineProxy);
	}
}

void CGameLogicGroup::addGameLogic(const std::string& logicName, std::shared_ptr<GameLogic> gameLogic)
{
	m_gameLogicsNameMap.emplace(logicName, std::move(gameLogic));
}

ComponentTypeId CGameLogicGroup::getTypeId()
{
	return Component::getTypeId<CGameLogicGroup>();
}