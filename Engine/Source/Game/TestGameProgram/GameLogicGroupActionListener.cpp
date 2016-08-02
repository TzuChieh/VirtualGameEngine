#include "GameLogicGroupActionListener.h"

#include <iostream>

using namespace xe;

void GameLogicGroupActionListener::onComponentAdded(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "GameLogicGroupActionListener: GameLogicGroup added action" << std::endl;
}

void GameLogicGroupActionListener::onComponentRemoval(const std::shared_ptr<ComponentHandle>& targetComponent)
{
	std::cout << "GameLogicGroupActionListener: GameLogicGroup removal action" << std::endl;
}