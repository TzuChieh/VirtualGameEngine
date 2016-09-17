#include "GameLogicGroupProcessor.h"
#include "Game/Component/CGameLogicGroup.h"

#include <iostream>

namespace ve
{

GameLogicGroupProcessor::~GameLogicGroupProcessor() = default;

void GameLogicGroupProcessor::onComponentAdded(CGameLogicGroup* component, const ComponentIndexType index)
{
	std::cout << "GameLogicGroupActionListener: GameLogicGroup added event" << std::endl;

	component->initGameLogics();
}

void GameLogicGroupProcessor::onComponentRemoval(CGameLogicGroup* component, const ComponentIndexType index)
{
	std::cout << "GameLogicGroupActionListener: GameLogicGroup removal event" << std::endl;

	// TODO
}

}// end namespace ve