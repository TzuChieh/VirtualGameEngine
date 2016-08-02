#include "CGameLogicGroup.h"
#include "Game/GameLogic/GameLogic.h"

using namespace xe;

CGameLogicGroup::~CGameLogicGroup()
{

}

void CGameLogicGroup::executeAll(float32 deltaS, Engine* engine)
{

}

void CGameLogicGroup::addGameLogic(const std::string& logicName, std::shared_ptr<GameLogic> gameLogic)
{
	m_gameLogicsNameMap.emplace(logicName, std::move(gameLogic));
}

std::shared_ptr<ComponentHandle> CGameLogicGroup::addToEngine(Engine* engine)
{
	return nullptr;
}

ComponentTypeId CGameLogicGroup::getTypeId()
{
	return Component::getTypeId<CGameLogicGroup>();
}