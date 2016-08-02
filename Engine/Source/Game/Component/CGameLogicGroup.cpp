#include "CGameLogicGroup.h"
#include "Game/GameLogic/GameLogic.h"
#include "Core/Engine.h"
#include "Game/GameProgram.h"

using namespace xe;

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

void CGameLogicGroup::executeGameLogics(float32 deltaS, Engine* engine)
{
	for(auto& keyValuePair : m_gameLogicsNameMap)
	{
		keyValuePair.second->execute(deltaS, engine);
	}
}

void CGameLogicGroup::addGameLogic(const std::string& logicName, std::shared_ptr<GameLogic> gameLogic)
{
	m_gameLogicsNameMap.emplace(logicName, std::move(gameLogic));
}

std::shared_ptr<ComponentHandle> CGameLogicGroup::addToEngine(Engine* engine)
{
	return engine->getGameProgram()->addGameLogicGroup(*this);
}

ComponentTypeId CGameLogicGroup::getTypeId()
{
	return Component::getTypeId<CGameLogicGroup>();
}